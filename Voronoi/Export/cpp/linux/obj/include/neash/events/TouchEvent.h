#ifndef INCLUDED_neash_events_TouchEvent
#define INCLUDED_neash_events_TouchEvent

#ifndef HXCPP_H
#include <hxcpp.h>
#endif

#include <neash/events/MouseEvent.h>
HX_DECLARE_CLASS2(neash,display,DisplayObject)
HX_DECLARE_CLASS2(neash,display,IBitmapDrawable)
HX_DECLARE_CLASS2(neash,display,InteractiveObject)
HX_DECLARE_CLASS2(neash,events,Event)
HX_DECLARE_CLASS2(neash,events,EventDispatcher)
HX_DECLARE_CLASS2(neash,events,IEventDispatcher)
HX_DECLARE_CLASS2(neash,events,MouseEvent)
HX_DECLARE_CLASS2(neash,events,TouchEvent)
HX_DECLARE_CLASS2(neash,geom,Point)
namespace neash{
namespace events{


class TouchEvent_obj : public ::neash::events::MouseEvent_obj{
	public:
		typedef ::neash::events::MouseEvent_obj super;
		typedef TouchEvent_obj OBJ_;
		TouchEvent_obj();
		Void __construct(::String type,hx::Null< bool >  __o_bubbles,hx::Null< bool >  __o_cancelable,hx::Null< Float >  __o_in_localX,hx::Null< Float >  __o_in_localY,hx::Null< Float >  __o_in_sizeX,hx::Null< Float >  __o_in_sizeY,::neash::display::InteractiveObject in_relatedObject,hx::Null< bool >  __o_in_ctrlKey,hx::Null< bool >  __o_in_altKey,hx::Null< bool >  __o_in_shiftKey,hx::Null< bool >  __o_in_buttonDown,hx::Null< int >  __o_in_delta,hx::Null< bool >  __o_in_commandKey,hx::Null< int >  __o_in_clickCount);

	public:
		static hx::ObjectPtr< TouchEvent_obj > __new(::String type,hx::Null< bool >  __o_bubbles,hx::Null< bool >  __o_cancelable,hx::Null< Float >  __o_in_localX,hx::Null< Float >  __o_in_localY,hx::Null< Float >  __o_in_sizeX,hx::Null< Float >  __o_in_sizeY,::neash::display::InteractiveObject in_relatedObject,hx::Null< bool >  __o_in_ctrlKey,hx::Null< bool >  __o_in_altKey,hx::Null< bool >  __o_in_shiftKey,hx::Null< bool >  __o_in_buttonDown,hx::Null< int >  __o_in_delta,hx::Null< bool >  __o_in_commandKey,hx::Null< int >  __o_in_clickCount);
		static Dynamic __CreateEmpty();
		static Dynamic __Create(hx::DynamicArray inArgs);
		~TouchEvent_obj();

		HX_DO_RTTI;
		static void __boot();
		static void __register();
		void __Mark(HX_MARK_PARAMS);
		void __Visit(HX_VISIT_PARAMS);
		::String __ToString() const { return HX_CSTRING("TouchEvent"); }

		virtual ::neash::events::MouseEvent nmeCreateSimilar( ::String inType,::neash::display::InteractiveObject related,::neash::display::InteractiveObject targ);

		Float sizeY; /* REM */ 
		Float sizeX; /* REM */ 
		int touchPointID; /* REM */ 
		bool isPrimaryTouchPoint; /* REM */ 
		static ::String TOUCH_BEGIN; /* REM */ 
		static ::String TOUCH_END; /* REM */ 
		static ::String TOUCH_MOVE; /* REM */ 
		static ::String TOUCH_OUT; /* REM */ 
		static ::String TOUCH_OVER; /* REM */ 
		static ::String TOUCH_ROLL_OUT; /* REM */ 
		static ::String TOUCH_ROLL_OVER; /* REM */ 
		static ::String TOUCH_TAP; /* REM */ 
		static ::neash::events::TouchEvent nmeCreate( ::String inType,Dynamic inEvent,::neash::geom::Point inLocal,::neash::display::InteractiveObject inTarget,Float sizeX,Float sizeY);
		static Dynamic nmeCreate_dyn();

};

} // end namespace neash
} // end namespace events

#endif /* INCLUDED_neash_events_TouchEvent */ 
