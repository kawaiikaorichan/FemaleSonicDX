#include "stdafx.h"

#include "SADXModLoader.h"
#include "Trampoline.h"
#include <stack>

#include "uiscale.h"

namespace uiscale
{
	FillMode bg_fill  = FillMode::fill;
	FillMode fmv_fill = FillMode::fit;

	float scale_min = 0.0f;
	float scale_max = 0.0f;
	float scale_h   = 0.0f;
	float scale_v   = 0.0f;
}

#pragma region Scale stack

struct ScaleEntry
{
	Uint8 alignment;
	NJS_POINT2 scale;
	bool is_background;
};

static std::stack<ScaleEntry, std::vector<ScaleEntry>> scale_stack;

static constexpr float THIRD_H = 640.0f / 3.0f;
static constexpr float THIRD_V = 480.0f / 3.0f;

static bool  sprite_scale = false;
static bool  do_scale     = false;
static bool  _do_scale    = false;
static float backup_h     = 0.0f;
static float backup_v     = 0.0f;

static NJS_POINT2 region_fit  = { 0.0f, 0.0f };
static NJS_POINT2 region_fill = { 0.0f, 0.0f };

void uiscale::update_parameters()
{
	scale_h = HorizontalStretch;
	scale_v = VerticalStretch;

	scale_min = min(scale_h, scale_v);
	scale_max = max(scale_h, scale_v);

	region_fit.x  = 640.0f * scale_min;
	region_fit.y  = 480.0f * scale_min;
	region_fill.x = 640.0f * scale_max;
	region_fill.y = 480.0f * scale_max;
}

bool uiscale::is_top_background()
{
	return !scale_stack.empty() && scale_stack.top().is_background;
}

bool uiscale::is_scale_enabled()
{
	return do_scale && (!is_top_background() || bg_fill != FillMode::stretch);
}

void uiscale::scale_push(Uint8 align, bool is_background, float h, float v)
{
#ifdef _DEBUG
	auto pad = ControllerPointers[0];
	if (pad && pad->HeldButtons & Buttons_Z)
	{
		return;
	}
#endif

	scale_stack.push({ align, { HorizontalStretch, VerticalStretch }, is_background });

	HorizontalStretch = h;
	VerticalStretch = v;

	do_scale = true;
}

void uiscale::scale_disable()
{
	backup_h = HorizontalStretch;
	backup_v = VerticalStretch;
	HorizontalStretch = scale_h;
	VerticalStretch = scale_v;
	_do_scale = do_scale;
	do_scale = false;
}

void uiscale::scale_enable()
{
	do_scale = _do_scale;

	if (do_scale)
	{
		HorizontalStretch = backup_h;
		VerticalStretch = backup_v;

		backup_h = backup_v = 0.0f;
	}
}

void uiscale::scale_pop()
{
	if (scale_stack.empty())
	{
		return;
	}

	auto point = scale_stack.top();
	HorizontalStretch = point.scale.x;
	VerticalStretch = point.scale.y;

	scale_stack.pop();
	do_scale = !scale_stack.empty();
}

static Trampoline* DisplayAllObjects_t = nullptr;

static void __cdecl DisplayAllObjects_r()
{
	using uiscale::Align;

	if (do_scale)
	{
		uiscale::scale_push(Align::automatic, false, uiscale::scale_h, uiscale::scale_v);
	}

	auto original = static_cast<decltype(DisplayAllObjects_r)*>(DisplayAllObjects_t->Target());
	original();

	if (do_scale)
	{
		uiscale::scale_pop();
	}
}

static NJS_POINT2 auto_align(Uint8 align, const NJS_POINT2& center)
{
	using namespace uiscale;

	if (align == Align::automatic)
	{
		if (center.x < THIRD_H)
		{
			align |= Align::left;
		}
		else if (center.x < THIRD_H * 2.0f)
		{
			align |= Align::horizontal_center;
		}
		else
		{
			align |= Align::right;
		}

		if (center.y < THIRD_V)
		{
			align |= Align::top;
		}
		else if (center.y < THIRD_V * 2.0f)
		{
			align |= Align::vertical_center;
		}
		else
		{
			align |= Align::bottom;
		}
	}

	NJS_POINT2 result = {};
	const auto h = static_cast<float>(HorizontalResolution);
	const auto v = static_cast<float>(VerticalResolution);

	if (align & Align::horizontal_center)
	{
		if (h / scale_v > 640.0f)
		{
			result.x = (h - region_fit.x) / 2.0f;
		}
	}
	else if (align & Align::right)
	{
		result.x = h - region_fit.x;
	}

	if (align & Align::vertical_center)
	{
		if (v / scale_h > 480.0f)
		{
			result.y = (v - region_fit.y) / 2.0f;
		}
	}
	else if (align & Align::bottom)
	{
		result.y = v - region_fit.y;
	}

	return result;
}

static NJS_POINT2 auto_align(Uint8 align, const NJS_POINT3& center)
{
	return auto_align(align, *reinterpret_cast<const NJS_POINT2*>(&center));
}

inline NJS_POINT2 get_offset(Uint8 align, const NJS_POINT2& center)
{
	NJS_POINT2 offset;

	// if we're scaling a background with fill mode, manually set
	// coordinate offset so the entire image lands in the center.
	if (uiscale::is_top_background() && uiscale::bg_fill == uiscale::FillMode::fill)
	{
		offset.x = (static_cast<float>(HorizontalResolution) - region_fill.x) / 2.0f;
		offset.y = (static_cast<float>(VerticalResolution) - region_fill.y) / 2.0f;
	}
	else
	{
		offset = auto_align(align, center);
	}

	return offset;
}

float uiscale::get_scale()
{
	return is_top_background() && bg_fill == FillMode::fill ? scale_max : scale_min;
}

/**
 * \brief Scales and re-positions an array of structures containing the fields x and y.
 * \tparam T A structure type containing the fields x and y.
 * \param points Pointer to an array of T.
 * \param count Length of the array
 */
template <typename T>
static void scale_points(T* points, size_t count)
{
	if (sprite_scale || scale_stack.empty())
	{
		return;
	}

	const auto& top = scale_stack.top();
	const Uint8 align = top.alignment;

	NJS_POINT2 center = {};
	const auto m = 1.0f / static_cast<float>(count);

	for (size_t i = 0; i < count; i++)
	{
		const auto& p = points[i];
		center.x += p.x * m;
		center.y += p.y * m;
	}

	const NJS_POINT2 offset = get_offset(align, center);
	const float scale = uiscale::get_scale();

	for (size_t i = 0; i < count; i++)
	{
		auto& p = points[i];
		p.x = p.x * scale + offset.x;
		p.y = p.y * scale + offset.y;
	}
}

static void scale_quad_ex(NJS_QUAD_TEXTURE_EX* quad)
{
	if (sprite_scale || scale_stack.empty())
	{
		return;
	}

	const auto& top = scale_stack.top();
	const Uint8 align = top.alignment;

	const NJS_POINT2 center = {
		quad->x + (quad->vx1 / 2.0f),
		quad->y + (quad->vy2 / 2.0f)
	};

	const NJS_POINT2 offset = get_offset(align, center);
	const float scale = uiscale::get_scale();

	quad->x = quad->x * scale + offset.x;
	quad->y = quad->y * scale + offset.y;
	quad->vx1 *= scale;
	quad->vy1 *= scale;
	quad->vx2 *= scale;
	quad->vy2 *= scale;
}

static NJS_SPRITE last_sprite = {};
static void __cdecl sprite_push(NJS_SPRITE* sp)
{
	using namespace uiscale;

	sprite_scale = true;

	if (scale_stack.empty())
	{
		return;
	}

	const auto& top = scale_stack.top();
	const Uint8 align = top.alignment;

	const NJS_POINT2 offset = auto_align(align, sp->p);

	last_sprite = *sp;

	sp->p.x = sp->p.x * scale_min + offset.x;
	sp->p.y = sp->p.y * scale_min + offset.y;
	sp->sx *= scale_min;
	sp->sy *= scale_min;
}

static void __cdecl sprite_pop(NJS_SPRITE* sp)
{
	sprite_scale = false;

	sp->p = last_sprite.p;
	sp->sx = last_sprite.sx;
	sp->sy = last_sprite.sy;
}

#pragma endregion

#pragma region Scale wrappers

static void __cdecl njDrawSprite2D_Queue_r(NJS_SPRITE *sp, Int n, Float pri, NJD_SPRITE attr, QueuedModelFlagsB queue_flags);
static void __cdecl Draw2DLinesMaybe_Queue_r(NJS_POINT2COL *points, int count, float depth, Uint32 attr, QueuedModelFlagsB flags);
static void __cdecl njDrawTriangle2D_r(NJS_POINT2COL *p, Int n, Float pri, Uint32 attr);
static void __cdecl Direct3D_DrawQuad_r(NJS_QUAD_TEXTURE_EX* quad);
static void __cdecl njDrawPolygon_r(NJS_POLYGON_VTX *polygon, Int count, Int trans);

// Must be initialized dynamically to fix a call instruction.
static Trampoline* njDrawTextureMemList_t = nullptr;
static Trampoline njDrawSprite2D_Queue_t(0x00404660, 0x00404666, njDrawSprite2D_Queue_r);
static Trampoline Draw2DLinesMaybe_Queue_t(0x00404490, 0x00404496, Draw2DLinesMaybe_Queue_r);
static Trampoline njDrawTriangle2D_t(0x0077E9F0, 0x0077E9F8, njDrawTriangle2D_r);
static Trampoline Direct3D_DrawQuad_t(0x0077DE10, 0x0077DE18, Direct3D_DrawQuad_r);
static Trampoline njDrawPolygon_t(0x0077DBC0, 0x0077DBC5, njDrawPolygon_r);

static void __cdecl njDrawSprite2D_Queue_r(NJS_SPRITE *sp, Int n, Float pri, NJD_SPRITE attr, QueuedModelFlagsB queue_flags)
{
	using namespace uiscale;

	if (sp == nullptr)
	{
		return;
	}

	NonStaticFunctionPointer(void, original, (NJS_SPRITE*, Int, Float, NJD_SPRITE, QueuedModelFlagsB), njDrawSprite2D_Queue_t.Target());

	// Scales lens flare and sun.
	// It uses njProjectScreen so there's no position scaling required.
	if (sp == reinterpret_cast<NJS_SPRITE*>(0x009BF3B0))
	{
		sp->sx *= scale_min;
		sp->sy *= scale_min;
		original(sp, n, pri, attr, queue_flags);
	}
	else if (uiscale::is_scale_enabled())
	{
		sprite_push(sp);
		original(sp, n, pri, attr | NJD_SPRITE_SCALE, queue_flags);
		sprite_pop(sp);
	}
	else
	{
		original(sp, n, pri, attr, queue_flags);
	}
}

static void __cdecl Draw2DLinesMaybe_Queue_r(NJS_POINT2COL *points, int count, float depth, Uint32 attr, QueuedModelFlagsB flags)
{
	auto original = static_cast<decltype(Draw2DLinesMaybe_Queue_r)*>(Draw2DLinesMaybe_Queue_t.Target());

	if (uiscale::is_scale_enabled())
	{
		scale_points(points->p, count);
	}

	original(points, count, depth, attr, flags);
}

static void __cdecl njDrawTextureMemList_r(NJS_TEXTURE_VTX *polygon, Int count, Int tex, Int flag)
{
	auto original = static_cast<decltype(njDrawTextureMemList_r)*>(njDrawTextureMemList_t->Target());

	if (uiscale::is_scale_enabled())
	{
		scale_points(polygon, count);
	}

	original(polygon, count, tex, flag);
}

static void __cdecl njDrawTriangle2D_r(NJS_POINT2COL *p, Int n, Float pri, Uint32 attr)
{
	auto original = static_cast<decltype(njDrawTriangle2D_r)*>(njDrawTriangle2D_t.Target());

	if (uiscale::is_scale_enabled())
	{
		auto _n = n;
		if (attr & (NJD_DRAW_FAN | NJD_DRAW_CONNECTED))
		{
			_n += 2;
		}
		else
		{
			_n *= 3;
		}

		scale_points(p->p, _n);
	}

	original(p, n, pri, attr);
}

static void __cdecl Direct3D_DrawQuad_r(NJS_QUAD_TEXTURE_EX* quad)
{
	auto original = static_cast<decltype(Direct3D_DrawQuad_r)*>(Direct3D_DrawQuad_t.Target());

	if (uiscale::is_scale_enabled())
	{
		scale_quad_ex(quad);
	}

	original(quad);
}

static void __cdecl njDrawPolygon_r(NJS_POLYGON_VTX* polygon, Int count, Int trans)
{
	auto orig = static_cast<decltype(njDrawPolygon_r)*>(njDrawPolygon_t.Target());

	if (uiscale::is_scale_enabled())
	{
		scale_points(polygon, count);
	}

	orig(polygon, count, trans);
}

static void njDrawTextureMemList_init()
{
	// This has to be created dynamically to repair a function call.
	if (njDrawTextureMemList_t == nullptr)
	{
		njDrawTextureMemList_t = new Trampoline(0x0077DC70, 0x0077DC79, njDrawTextureMemList_r);
		WriteCall(reinterpret_cast<void*>(reinterpret_cast<size_t>(njDrawTextureMemList_t->Target()) + 4), njAlphaMode);
	}
}

#pragma endregion

#pragma region HUD scaling

void uiscale::initialize()
{
	update_parameters();
	njDrawTextureMemList_init();

	DisplayAllObjects_t = new Trampoline(0x0040B540, 0x0040B546, DisplayAllObjects_r);
	WriteCall(reinterpret_cast<void*>(reinterpret_cast<size_t>(DisplayAllObjects_t->Target()) + 1), reinterpret_cast<void*>(0x004128F0));
}

#pragma endregion

#pragma region Background scaling

void uiscale::setup_background_scale()
{
	update_parameters();
	njDrawTextureMemList_init();
}

#pragma endregion

#pragma region FMV scaling

static Trampoline* DisplayVideoFrame_t = nullptr;

static void __cdecl DisplayVideoFrame_r(int width, int height)
{
	using namespace uiscale;

	auto orig = bg_fill;
	bg_fill = fmv_fill;
	scale_trampoline(center, true, DisplayVideoFrame_r, DisplayVideoFrame_t, width, height);
	bg_fill = orig;
}

void uiscale::setup_fmv_scale()
{
	update_parameters();
	njDrawTextureMemList_init();

	DisplayVideoFrame_t = new Trampoline(0x005139F0, 0x005139F5, DisplayVideoFrame_r);
}

#pragma endregion
