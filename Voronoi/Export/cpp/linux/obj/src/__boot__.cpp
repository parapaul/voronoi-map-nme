#include <hxcpp.h>

#include <sys/io/FileSeek.h>
#include <sys/io/FileOutput.h>
#include <sys/io/FileInput.h>
#include <sys/io/File.h>
#include <sys/FileSystem.h>
#include <sys/_FileSystem/FileKind.h>
#include <nme/ObjectHash.h>
#include <nme/Lib.h>
#include <neash/utils/WeakRef.h>
#include <neash/utils/Endian.h>
#include <neash/utils/ByteArray.h>
#include <neash/utils/IDataInput.h>
#include <neash/net/URLVariables.h>
#include <neash/net/URLRequestMethod.h>
#include <neash/net/URLRequestHeader.h>
#include <neash/net/URLRequest.h>
#include <neash/net/URLLoaderDataFormat.h>
#include <neash/net/URLLoader.h>
#include <neash/media/SoundTransform.h>
#include <neash/media/SoundChannel.h>
#include <neash/geom/Transform.h>
#include <neash/geom/Rectangle.h>
#include <neash/geom/Point.h>
#include <neash/geom/Matrix.h>
#include <neash/geom/ColorTransform.h>
#include <neash/filters/BitmapFilter.h>
#include <neash/events/SampleDataEvent.h>
#include <neash/events/ProgressEvent.h>
#include <neash/events/KeyboardEvent.h>
#include <neash/events/JoystickEvent.h>
#include <neash/events/IOErrorEvent.h>
#include <neash/events/HTTPStatusEvent.h>
#include <neash/events/FocusEvent.h>
#include <neash/events/EventPhase.h>
#include <neash/events/Listener.h>
#include <neash/events/ErrorEvent.h>
#include <neash/events/TextEvent.h>
#include <neash/errors/RangeError.h>
#include <neash/errors/EOFError.h>
#include <neash/errors/ArgumentError.h>
#include <neash/errors/Error.h>
#include <neash/display/TriangleCulling.h>
#include <neash/display/Tilesheet.h>
#include <neash/display/StageScaleMode.h>
#include <neash/display/StageQuality.h>
#include <neash/display/StageDisplayState.h>
#include <neash/display/StageAlign.h>
#include <neash/display/TouchInfo.h>
#include <neash/display/SpreadMethod.h>
#include <neash/display/Shape.h>
#include <neash/display/PixelSnapping.h>
#include <neash/display/MovieClip.h>
#include <neash/display/ManagedStage.h>
#include <neash/display/Stage.h>
#include <neash/events/TouchEvent.h>
#include <neash/events/MouseEvent.h>
#include <neash/events/Event.h>
#include <neash/display/LineScaleMode.h>
#include <neash/display/JointStyle.h>
#include <neash/display/InterpolationMethod.h>
#include <neash/display/IGraphicsData.h>
#include <neash/display/GraphicsPathWinding.h>
#include <neash/display/Graphics.h>
#include <neash/display/GradientType.h>
#include <neash/display/CapsStyle.h>
#include <neash/display/BlendMode.h>
#include <neash/display/OptimizedPerlin.h>
#include <neash/display/BitmapData.h>
#include <neash/display/Bitmap.h>
#include <neash/Lib.h>
#include <haxe/io/Error.h>
#include <haxe/io/Eof.h>
#include <haxe/io/BytesBuffer.h>
#include <haxe/Timer.h>
#include <haxe/Log.h>
#include <graph/Edge.h>
#include <graph/Corner.h>
#include <graph/Center.h>
#include <de/polygonal/math/PM_PRNG.h>
#include <cpp/zip/Uncompress.h>
#include <cpp/zip/Flush.h>
#include <cpp/zip/Compress.h>
#include <cpp/rtti/FieldNumericIntegerLookup.h>
#include <com/nodename/geom/Winding.h>
#include <com/nodename/geom/Polygon.h>
#include <com/nodename/geom/LineSegment.h>
#include <com/nodename/geom/Circle.h>
#include <com/nodename/delaunay/Voronoi.h>
#include <com/nodename/delaunay/Vertex.h>
#include <com/nodename/delaunay/Triangle.h>
#include <com/nodename/delaunay/SiteList.h>
#include <com/nodename/delaunay/Site.h>
#include <com/nodename/delaunay/Node.h>
#include <com/nodename/delaunay/LR.h>
#include <com/nodename/delaunay/Kruskal.h>
#include <com/nodename/delaunay/ICoord.h>
#include <com/nodename/delaunay/HalfedgePriorityQueue.h>
#include <com/nodename/delaunay/Halfedge.h>
#include <com/nodename/delaunay/EdgeReorderer.h>
#include <com/nodename/delaunay/Criterion.h>
#include <com/nodename/delaunay/EdgeList.h>
#include <com/nodename/utils/IDisposable.h>
#include <com/nodename/delaunay/Edge.h>
#include <com/nodename/delaunay/Delaunay.h>
#include <com/nodename/delaunay/BoundsCheck.h>
#include <co/janicek/core/math/PerlinNoise.h>
#include <co/janicek/core/array/Array2dValueIterator.h>
#include <co/janicek/core/array/Array2dIterator.h>
#include <co/janicek/core/array/Array2dCore.h>
#include <Watersheds.h>
#include <VoronoiDashboard.h>
#include <neash/geom/Vector3D.h>
#include <neash/display/Sprite.h>
#include <neash/display/DisplayObjectContainer.h>
#include <neash/display/InteractiveObject.h>
#include <neash/display/DisplayObject.h>
#include <sys/io/_Process/Stdout.h>
#include <haxe/io/Input.h>
#include <haxe/io/Bytes.h>
#include <sys/io/_Process/Stdin.h>
#include <haxe/io/Output.h>
#include <sys/io/Process.h>
#include <neash/Loader.h>
#include <neash/display/IBitmapDrawable.h>
#include <neash/events/EventDispatcher.h>
#include <neash/events/IEventDispatcher.h>
#include <Type.h>
#include <ValueType.h>
#include <Sys.h>
#include <cpp/Lib.h>
#include <StringTools.h>
#include <StringBuf.h>
#include <Std.h>
#include <Roads.h>
#include <Reflect.h>
#include <NullHelper.h>
#include <NoisyEdges.h>
#include <IslandShape.h>
#include <Map.h>
#include <List.h>
#include <Lava.h>
#include <Lambda.h>
#include <IntIter.h>
#include <IntHash.h>
#include <Hash.h>
#include <Date.h>
#include <ApplicationMain.h>

void __boot_all()
{
hx::RegisterResources( hx::GetResources() );
::sys::io::FileSeek_obj::__register();
::sys::io::FileOutput_obj::__register();
::sys::io::FileInput_obj::__register();
::sys::io::File_obj::__register();
::sys::FileSystem_obj::__register();
::sys::_FileSystem::FileKind_obj::__register();
::nme::ObjectHash_obj::__register();
::nme::Lib_obj::__register();
::neash::utils::WeakRef_obj::__register();
::neash::utils::Endian_obj::__register();
::neash::utils::ByteArray_obj::__register();
::neash::utils::IDataInput_obj::__register();
::neash::net::URLVariables_obj::__register();
::neash::net::URLRequestMethod_obj::__register();
::neash::net::URLRequestHeader_obj::__register();
::neash::net::URLRequest_obj::__register();
::neash::net::URLLoaderDataFormat_obj::__register();
::neash::net::URLLoader_obj::__register();
::neash::media::SoundTransform_obj::__register();
::neash::media::SoundChannel_obj::__register();
::neash::geom::Transform_obj::__register();
::neash::geom::Rectangle_obj::__register();
::neash::geom::Point_obj::__register();
::neash::geom::Matrix_obj::__register();
::neash::geom::ColorTransform_obj::__register();
::neash::filters::BitmapFilter_obj::__register();
::neash::events::SampleDataEvent_obj::__register();
::neash::events::ProgressEvent_obj::__register();
::neash::events::KeyboardEvent_obj::__register();
::neash::events::JoystickEvent_obj::__register();
::neash::events::IOErrorEvent_obj::__register();
::neash::events::HTTPStatusEvent_obj::__register();
::neash::events::FocusEvent_obj::__register();
::neash::events::EventPhase_obj::__register();
::neash::events::Listener_obj::__register();
::neash::events::ErrorEvent_obj::__register();
::neash::events::TextEvent_obj::__register();
::neash::errors::RangeError_obj::__register();
::neash::errors::EOFError_obj::__register();
::neash::errors::ArgumentError_obj::__register();
::neash::errors::Error_obj::__register();
::neash::display::TriangleCulling_obj::__register();
::neash::display::Tilesheet_obj::__register();
::neash::display::StageScaleMode_obj::__register();
::neash::display::StageQuality_obj::__register();
::neash::display::StageDisplayState_obj::__register();
::neash::display::StageAlign_obj::__register();
::neash::display::TouchInfo_obj::__register();
::neash::display::SpreadMethod_obj::__register();
::neash::display::Shape_obj::__register();
::neash::display::PixelSnapping_obj::__register();
::neash::display::MovieClip_obj::__register();
::neash::display::ManagedStage_obj::__register();
::neash::display::Stage_obj::__register();
::neash::events::TouchEvent_obj::__register();
::neash::events::MouseEvent_obj::__register();
::neash::events::Event_obj::__register();
::neash::display::LineScaleMode_obj::__register();
::neash::display::JointStyle_obj::__register();
::neash::display::InterpolationMethod_obj::__register();
::neash::display::IGraphicsData_obj::__register();
::neash::display::GraphicsPathWinding_obj::__register();
::neash::display::Graphics_obj::__register();
::neash::display::GradientType_obj::__register();
::neash::display::CapsStyle_obj::__register();
::neash::display::BlendMode_obj::__register();
::neash::display::OptimizedPerlin_obj::__register();
::neash::display::BitmapData_obj::__register();
::neash::display::Bitmap_obj::__register();
::neash::Lib_obj::__register();
::haxe::io::Error_obj::__register();
::haxe::io::Eof_obj::__register();
::haxe::io::BytesBuffer_obj::__register();
::haxe::Timer_obj::__register();
::haxe::Log_obj::__register();
::graph::Edge_obj::__register();
::graph::Corner_obj::__register();
::graph::Center_obj::__register();
::de::polygonal::math::PM_PRNG_obj::__register();
::cpp::zip::Uncompress_obj::__register();
::cpp::zip::Flush_obj::__register();
::cpp::zip::Compress_obj::__register();
::cpp::rtti::FieldNumericIntegerLookup_obj::__register();
::com::nodename::geom::Winding_obj::__register();
::com::nodename::geom::Polygon_obj::__register();
::com::nodename::geom::LineSegment_obj::__register();
::com::nodename::geom::Circle_obj::__register();
::com::nodename::delaunay::Voronoi_obj::__register();
::com::nodename::delaunay::Vertex_obj::__register();
::com::nodename::delaunay::Triangle_obj::__register();
::com::nodename::delaunay::SiteList_obj::__register();
::com::nodename::delaunay::Site_obj::__register();
::com::nodename::delaunay::Node_obj::__register();
::com::nodename::delaunay::LR_obj::__register();
::com::nodename::delaunay::Kruskal_obj::__register();
::com::nodename::delaunay::ICoord_obj::__register();
::com::nodename::delaunay::HalfedgePriorityQueue_obj::__register();
::com::nodename::delaunay::Halfedge_obj::__register();
::com::nodename::delaunay::EdgeReorderer_obj::__register();
::com::nodename::delaunay::Criterion_obj::__register();
::com::nodename::delaunay::EdgeList_obj::__register();
::com::nodename::utils::IDisposable_obj::__register();
::com::nodename::delaunay::Edge_obj::__register();
::com::nodename::delaunay::Delaunay_obj::__register();
::com::nodename::delaunay::BoundsCheck_obj::__register();
::co::janicek::core::math::PerlinNoise_obj::__register();
::co::janicek::core::array::Array2dValueIterator_obj::__register();
::co::janicek::core::array::Array2dIterator_obj::__register();
::co::janicek::core::array::Array2dCore_obj::__register();
::Watersheds_obj::__register();
::VoronoiDashboard_obj::__register();
::neash::geom::Vector3D_obj::__register();
::neash::display::Sprite_obj::__register();
::neash::display::DisplayObjectContainer_obj::__register();
::neash::display::InteractiveObject_obj::__register();
::neash::display::DisplayObject_obj::__register();
::sys::io::_Process::Stdout_obj::__register();
::haxe::io::Input_obj::__register();
::haxe::io::Bytes_obj::__register();
::sys::io::_Process::Stdin_obj::__register();
::haxe::io::Output_obj::__register();
::sys::io::Process_obj::__register();
::neash::Loader_obj::__register();
::neash::display::IBitmapDrawable_obj::__register();
::neash::events::EventDispatcher_obj::__register();
::neash::events::IEventDispatcher_obj::__register();
::Type_obj::__register();
::ValueType_obj::__register();
::Sys_obj::__register();
::cpp::Lib_obj::__register();
::StringTools_obj::__register();
::StringBuf_obj::__register();
::Std_obj::__register();
::Roads_obj::__register();
::Reflect_obj::__register();
::NullHelper_obj::__register();
::NoisyEdges_obj::__register();
::IslandShape_obj::__register();
::Map_obj::__register();
::List_obj::__register();
::Lava_obj::__register();
::Lambda_obj::__register();
::IntIter_obj::__register();
::IntHash_obj::__register();
::Hash_obj::__register();
::Date_obj::__register();
::ApplicationMain_obj::__register();
::neash::utils::ByteArray_obj::__init__();
::cpp::Lib_obj::__boot();
::cpp::rtti::FieldNumericIntegerLookup_obj::__boot();
::cpp::zip::Compress_obj::__boot();
::cpp::zip::Flush_obj::__boot();
::cpp::zip::Uncompress_obj::__boot();
::haxe::Log_obj::__boot();
::ApplicationMain_obj::__boot();
::Date_obj::__boot();
::Hash_obj::__boot();
::IntHash_obj::__boot();
::IntIter_obj::__boot();
::Lambda_obj::__boot();
::Lava_obj::__boot();
::List_obj::__boot();
::Map_obj::__boot();
::IslandShape_obj::__boot();
::NoisyEdges_obj::__boot();
::NullHelper_obj::__boot();
::Reflect_obj::__boot();
::Roads_obj::__boot();
::Std_obj::__boot();
::StringBuf_obj::__boot();
::StringTools_obj::__boot();
::Sys_obj::__boot();
::ValueType_obj::__boot();
::Type_obj::__boot();
::neash::events::IEventDispatcher_obj::__boot();
::neash::events::EventDispatcher_obj::__boot();
::neash::display::IBitmapDrawable_obj::__boot();
::neash::Loader_obj::__boot();
::sys::io::Process_obj::__boot();
::haxe::io::Output_obj::__boot();
::sys::io::_Process::Stdin_obj::__boot();
::haxe::io::Bytes_obj::__boot();
::haxe::io::Input_obj::__boot();
::sys::io::_Process::Stdout_obj::__boot();
::neash::display::DisplayObject_obj::__boot();
::neash::display::InteractiveObject_obj::__boot();
::neash::display::DisplayObjectContainer_obj::__boot();
::neash::display::Sprite_obj::__boot();
::neash::geom::Vector3D_obj::__boot();
::VoronoiDashboard_obj::__boot();
::Watersheds_obj::__boot();
::co::janicek::core::array::Array2dCore_obj::__boot();
::co::janicek::core::array::Array2dIterator_obj::__boot();
::co::janicek::core::array::Array2dValueIterator_obj::__boot();
::co::janicek::core::math::PerlinNoise_obj::__boot();
::com::nodename::delaunay::BoundsCheck_obj::__boot();
::com::nodename::delaunay::Delaunay_obj::__boot();
::com::nodename::delaunay::Edge_obj::__boot();
::com::nodename::utils::IDisposable_obj::__boot();
::com::nodename::delaunay::EdgeList_obj::__boot();
::com::nodename::delaunay::Criterion_obj::__boot();
::com::nodename::delaunay::EdgeReorderer_obj::__boot();
::com::nodename::delaunay::Halfedge_obj::__boot();
::com::nodename::delaunay::HalfedgePriorityQueue_obj::__boot();
::com::nodename::delaunay::ICoord_obj::__boot();
::com::nodename::delaunay::Kruskal_obj::__boot();
::com::nodename::delaunay::LR_obj::__boot();
::com::nodename::delaunay::Node_obj::__boot();
::com::nodename::delaunay::Site_obj::__boot();
::com::nodename::delaunay::SiteList_obj::__boot();
::com::nodename::delaunay::Triangle_obj::__boot();
::com::nodename::delaunay::Vertex_obj::__boot();
::com::nodename::delaunay::Voronoi_obj::__boot();
::com::nodename::geom::Circle_obj::__boot();
::com::nodename::geom::LineSegment_obj::__boot();
::com::nodename::geom::Polygon_obj::__boot();
::com::nodename::geom::Winding_obj::__boot();
::de::polygonal::math::PM_PRNG_obj::__boot();
::graph::Center_obj::__boot();
::graph::Corner_obj::__boot();
::graph::Edge_obj::__boot();
::haxe::Timer_obj::__boot();
::haxe::io::BytesBuffer_obj::__boot();
::haxe::io::Eof_obj::__boot();
::haxe::io::Error_obj::__boot();
::neash::Lib_obj::__boot();
::neash::display::Bitmap_obj::__boot();
::neash::display::BitmapData_obj::__boot();
::neash::display::OptimizedPerlin_obj::__boot();
::neash::display::BlendMode_obj::__boot();
::neash::display::CapsStyle_obj::__boot();
::neash::display::GradientType_obj::__boot();
::neash::display::Graphics_obj::__boot();
::neash::display::GraphicsPathWinding_obj::__boot();
::neash::display::IGraphicsData_obj::__boot();
::neash::display::InterpolationMethod_obj::__boot();
::neash::display::JointStyle_obj::__boot();
::neash::display::LineScaleMode_obj::__boot();
::neash::events::Event_obj::__boot();
::neash::events::MouseEvent_obj::__boot();
::neash::events::TouchEvent_obj::__boot();
::neash::display::Stage_obj::__boot();
::neash::display::ManagedStage_obj::__boot();
::neash::display::MovieClip_obj::__boot();
::neash::display::PixelSnapping_obj::__boot();
::neash::display::Shape_obj::__boot();
::neash::display::SpreadMethod_obj::__boot();
::neash::display::TouchInfo_obj::__boot();
::neash::display::StageAlign_obj::__boot();
::neash::display::StageDisplayState_obj::__boot();
::neash::display::StageQuality_obj::__boot();
::neash::display::StageScaleMode_obj::__boot();
::neash::display::Tilesheet_obj::__boot();
::neash::display::TriangleCulling_obj::__boot();
::neash::errors::Error_obj::__boot();
::neash::errors::ArgumentError_obj::__boot();
::neash::errors::EOFError_obj::__boot();
::neash::errors::RangeError_obj::__boot();
::neash::events::TextEvent_obj::__boot();
::neash::events::ErrorEvent_obj::__boot();
::neash::events::Listener_obj::__boot();
::neash::events::EventPhase_obj::__boot();
::neash::events::FocusEvent_obj::__boot();
::neash::events::HTTPStatusEvent_obj::__boot();
::neash::events::IOErrorEvent_obj::__boot();
::neash::events::JoystickEvent_obj::__boot();
::neash::events::KeyboardEvent_obj::__boot();
::neash::events::ProgressEvent_obj::__boot();
::neash::events::SampleDataEvent_obj::__boot();
::neash::filters::BitmapFilter_obj::__boot();
::neash::geom::ColorTransform_obj::__boot();
::neash::geom::Matrix_obj::__boot();
::neash::geom::Point_obj::__boot();
::neash::geom::Rectangle_obj::__boot();
::neash::geom::Transform_obj::__boot();
::neash::media::SoundChannel_obj::__boot();
::neash::media::SoundTransform_obj::__boot();
::neash::net::URLLoader_obj::__boot();
::neash::net::URLLoaderDataFormat_obj::__boot();
::neash::net::URLRequest_obj::__boot();
::neash::net::URLRequestHeader_obj::__boot();
::neash::net::URLRequestMethod_obj::__boot();
::neash::net::URLVariables_obj::__boot();
::neash::utils::IDataInput_obj::__boot();
::neash::utils::ByteArray_obj::__boot();
::neash::utils::Endian_obj::__boot();
::neash::utils::WeakRef_obj::__boot();
::nme::Lib_obj::__boot();
::nme::ObjectHash_obj::__boot();
::sys::_FileSystem::FileKind_obj::__boot();
::sys::FileSystem_obj::__boot();
::sys::io::File_obj::__boot();
::sys::io::FileInput_obj::__boot();
::sys::io::FileOutput_obj::__boot();
::sys::io::FileSeek_obj::__boot();
}

