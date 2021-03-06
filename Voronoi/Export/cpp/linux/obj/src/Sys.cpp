#include <hxcpp.h>

#ifndef INCLUDED_Hash
#include <Hash.h>
#endif
#ifndef INCLUDED_Sys
#include <Sys.h>
#endif
#ifndef INCLUDED_cpp_Lib
#include <cpp/Lib.h>
#endif
#ifndef INCLUDED_haxe_io_Input
#include <haxe/io/Input.h>
#endif
#ifndef INCLUDED_haxe_io_Output
#include <haxe/io/Output.h>
#endif
#ifndef INCLUDED_sys_io_FileInput
#include <sys/io/FileInput.h>
#endif
#ifndef INCLUDED_sys_io_FileOutput
#include <sys/io/FileOutput.h>
#endif

Void Sys_obj::__construct()
{
	return null();
}

Sys_obj::~Sys_obj() { }

Dynamic Sys_obj::__CreateEmpty() { return  new Sys_obj; }
hx::ObjectPtr< Sys_obj > Sys_obj::__new()
{  hx::ObjectPtr< Sys_obj > result = new Sys_obj();
	result->__construct();
	return result;}

Dynamic Sys_obj::__Create(hx::DynamicArray inArgs)
{  hx::ObjectPtr< Sys_obj > result = new Sys_obj();
	result->__construct();
	return result;}

Void Sys_obj::print( Dynamic v){
{
		HX_STACK_PUSH("Sys::print","/usr/lib/haxe/std/cpp/_std/Sys.hx",28);
		HX_STACK_ARG(v,"v");
		HX_STACK_LINE(28)
		::__hxcpp_print(v);
	}
return null();
}


STATIC_HX_DEFINE_DYNAMIC_FUNC1(Sys_obj,print,(void))

Void Sys_obj::println( Dynamic v){
{
		HX_STACK_PUSH("Sys::println","/usr/lib/haxe/std/cpp/_std/Sys.hx",32);
		HX_STACK_ARG(v,"v");
		HX_STACK_LINE(33)
		::Sys_obj::print(v);
		HX_STACK_LINE(34)
		::Sys_obj::print(HX_CSTRING("\n"));
	}
return null();
}


STATIC_HX_DEFINE_DYNAMIC_FUNC1(Sys_obj,println,(void))

::haxe::io::Input Sys_obj::_stdin( ){
	HX_STACK_PUSH("Sys::stdin","/usr/lib/haxe/std/cpp/_std/Sys.hx",37);
	HX_STACK_LINE(37)
	return ::sys::io::FileInput_obj::__new(::Sys_obj::file_stdin());
}


STATIC_HX_DEFINE_DYNAMIC_FUNC0(Sys_obj,_stdin,return )

::haxe::io::Output Sys_obj::_stdout( ){
	HX_STACK_PUSH("Sys::stdout","/usr/lib/haxe/std/cpp/_std/Sys.hx",41);
	HX_STACK_LINE(41)
	return ::sys::io::FileOutput_obj::__new(::Sys_obj::file_stdout());
}


STATIC_HX_DEFINE_DYNAMIC_FUNC0(Sys_obj,_stdout,return )

::haxe::io::Output Sys_obj::_stderr( ){
	HX_STACK_PUSH("Sys::stderr","/usr/lib/haxe/std/cpp/_std/Sys.hx",45);
	HX_STACK_LINE(45)
	return ::sys::io::FileOutput_obj::__new(::Sys_obj::file_stderr());
}


STATIC_HX_DEFINE_DYNAMIC_FUNC0(Sys_obj,_stderr,return )

int Sys_obj::getChar( bool echo){
	HX_STACK_PUSH("Sys::getChar","/usr/lib/haxe/std/cpp/_std/Sys.hx",49);
	HX_STACK_ARG(echo,"echo");
	HX_STACK_LINE(49)
	return ::Sys_obj::getch(echo);
}


STATIC_HX_DEFINE_DYNAMIC_FUNC1(Sys_obj,getChar,return )

Array< ::String > Sys_obj::args( ){
	HX_STACK_PUSH("Sys::args","/usr/lib/haxe/std/cpp/_std/Sys.hx",53);
	HX_STACK_LINE(53)
	return ::__get_args();
}


STATIC_HX_DEFINE_DYNAMIC_FUNC0(Sys_obj,args,return )

::String Sys_obj::getEnv( ::String s){
	HX_STACK_PUSH("Sys::getEnv","/usr/lib/haxe/std/cpp/_std/Sys.hx",57);
	HX_STACK_ARG(s,"s");
	HX_STACK_LINE(58)
	::String v = ::Sys_obj::get_env(s);		HX_STACK_VAR(v,"v");
	HX_STACK_LINE(59)
	if (((v == null()))){
		HX_STACK_LINE(60)
		return null();
	}
	HX_STACK_LINE(61)
	return v;
}


STATIC_HX_DEFINE_DYNAMIC_FUNC1(Sys_obj,getEnv,return )

Void Sys_obj::putEnv( ::String s,::String v){
{
		HX_STACK_PUSH("Sys::putEnv","/usr/lib/haxe/std/cpp/_std/Sys.hx",64);
		HX_STACK_ARG(s,"s");
		HX_STACK_ARG(v,"v");
		HX_STACK_LINE(64)
		::Sys_obj::put_env(s,v);
	}
return null();
}


STATIC_HX_DEFINE_DYNAMIC_FUNC2(Sys_obj,putEnv,(void))

Void Sys_obj::sleep( Float seconds){
{
		HX_STACK_PUSH("Sys::sleep","/usr/lib/haxe/std/cpp/_std/Sys.hx",68);
		HX_STACK_ARG(seconds,"seconds");
		HX_STACK_LINE(68)
		::Sys_obj::_sleep(seconds);
	}
return null();
}


STATIC_HX_DEFINE_DYNAMIC_FUNC1(Sys_obj,sleep,(void))

bool Sys_obj::setTimeLocale( ::String loc){
	HX_STACK_PUSH("Sys::setTimeLocale","/usr/lib/haxe/std/cpp/_std/Sys.hx",72);
	HX_STACK_ARG(loc,"loc");
	HX_STACK_LINE(72)
	return ::Sys_obj::set_time_locale(loc);
}


STATIC_HX_DEFINE_DYNAMIC_FUNC1(Sys_obj,setTimeLocale,return )

::String Sys_obj::getCwd( ){
	HX_STACK_PUSH("Sys::getCwd","/usr/lib/haxe/std/cpp/_std/Sys.hx",76);
	HX_STACK_LINE(76)
	return ::String(::Sys_obj::get_cwd());
}


STATIC_HX_DEFINE_DYNAMIC_FUNC0(Sys_obj,getCwd,return )

Void Sys_obj::setCwd( ::String s){
{
		HX_STACK_PUSH("Sys::setCwd","/usr/lib/haxe/std/cpp/_std/Sys.hx",80);
		HX_STACK_ARG(s,"s");
		HX_STACK_LINE(80)
		::Sys_obj::set_cwd(s);
	}
return null();
}


STATIC_HX_DEFINE_DYNAMIC_FUNC1(Sys_obj,setCwd,(void))

::String Sys_obj::systemName( ){
	HX_STACK_PUSH("Sys::systemName","/usr/lib/haxe/std/cpp/_std/Sys.hx",84);
	HX_STACK_LINE(84)
	return ::Sys_obj::sys_string();
}


STATIC_HX_DEFINE_DYNAMIC_FUNC0(Sys_obj,systemName,return )

::String Sys_obj::escapeArgument( ::String arg){
	HX_STACK_PUSH("Sys::escapeArgument","/usr/lib/haxe/std/cpp/_std/Sys.hx",88);
	HX_STACK_ARG(arg,"arg");
	HX_STACK_LINE(89)
	bool ok = true;		HX_STACK_VAR(ok,"ok");
	HX_STACK_LINE(90)
	{
		HX_STACK_LINE(90)
		int _g1 = (int)0;		HX_STACK_VAR(_g1,"_g1");
		int _g = arg.length;		HX_STACK_VAR(_g,"_g");
		HX_STACK_LINE(90)
		while(((_g1 < _g))){
			HX_STACK_LINE(90)
			int i = (_g1)++;		HX_STACK_VAR(i,"i");
			HX_STACK_LINE(91)
			switch( (int)(arg.charCodeAt(i))){
				case (int)32: case (int)34: {
					HX_STACK_LINE(92)
					ok = false;
				}
				;break;
				case (int)0: case (int)13: case (int)10: {
					HX_STACK_LINE(94)
					arg = arg.substr((int)0,i);
				}
				;break;
			}
		}
	}
	HX_STACK_LINE(97)
	if ((ok)){
		HX_STACK_LINE(98)
		return arg;
	}
	HX_STACK_LINE(99)
	return ((HX_CSTRING("\"") + arg.split(HX_CSTRING("\""))->join(HX_CSTRING("\\\""))) + HX_CSTRING("\""));
}


STATIC_HX_DEFINE_DYNAMIC_FUNC1(Sys_obj,escapeArgument,return )

int Sys_obj::command( ::String cmd,Array< ::String > args){
	HX_STACK_PUSH("Sys::command","/usr/lib/haxe/std/cpp/_std/Sys.hx",102);
	HX_STACK_ARG(cmd,"cmd");
	HX_STACK_ARG(args,"args");
	HX_STACK_LINE(103)
	if (((args != null()))){
		HX_STACK_LINE(104)
		cmd = ::Sys_obj::escapeArgument(cmd);
		HX_STACK_LINE(105)
		{
			HX_STACK_LINE(105)
			int _g = (int)0;		HX_STACK_VAR(_g,"_g");
			HX_STACK_LINE(105)
			while(((_g < args->length))){
				HX_STACK_LINE(105)
				::String a = args->__get(_g);		HX_STACK_VAR(a,"a");
				HX_STACK_LINE(105)
				++(_g);
				HX_STACK_LINE(106)
				hx::AddEq(cmd,(HX_CSTRING(" ") + ::Sys_obj::escapeArgument(a)));
			}
		}
	}
	HX_STACK_LINE(108)
	return ::Sys_obj::sys_command(cmd);
}


STATIC_HX_DEFINE_DYNAMIC_FUNC2(Sys_obj,command,return )

Void Sys_obj::exit( int code){
{
		HX_STACK_PUSH("Sys::exit","/usr/lib/haxe/std/cpp/_std/Sys.hx",111);
		HX_STACK_ARG(code,"code");
		HX_STACK_LINE(111)
		::Sys_obj::sys_exit(code);
	}
return null();
}


STATIC_HX_DEFINE_DYNAMIC_FUNC1(Sys_obj,exit,(void))

Float Sys_obj::time( ){
	HX_STACK_PUSH("Sys::time","/usr/lib/haxe/std/cpp/_std/Sys.hx",115);
	HX_STACK_LINE(115)
	return ::Sys_obj::sys_time();
}


STATIC_HX_DEFINE_DYNAMIC_FUNC0(Sys_obj,time,return )

Float Sys_obj::cpuTime( ){
	HX_STACK_PUSH("Sys::cpuTime","/usr/lib/haxe/std/cpp/_std/Sys.hx",119);
	HX_STACK_LINE(119)
	return ::Sys_obj::sys_cpu_time();
}


STATIC_HX_DEFINE_DYNAMIC_FUNC0(Sys_obj,cpuTime,return )

::String Sys_obj::executablePath( ){
	HX_STACK_PUSH("Sys::executablePath","/usr/lib/haxe/std/cpp/_std/Sys.hx",123);
	HX_STACK_LINE(123)
	return ::String(::Sys_obj::sys_exe_path());
}


STATIC_HX_DEFINE_DYNAMIC_FUNC0(Sys_obj,executablePath,return )

::Hash Sys_obj::environment( ){
	HX_STACK_PUSH("Sys::environment","/usr/lib/haxe/std/cpp/_std/Sys.hx",127);
	HX_STACK_LINE(128)
	Array< ::String > vars = ::Sys_obj::sys_env();		HX_STACK_VAR(vars,"vars");
	HX_STACK_LINE(129)
	::Hash result = ::Hash_obj::__new();		HX_STACK_VAR(result,"result");
	HX_STACK_LINE(130)
	int i = (int)0;		HX_STACK_VAR(i,"i");
	HX_STACK_LINE(131)
	while(((i < vars->length))){
		HX_STACK_LINE(132)
		result->set(vars->__get(i),vars->__get((i + (int)1)));
		HX_STACK_LINE(133)
		hx::AddEq(i,(int)2);
	}
	HX_STACK_LINE(135)
	return result;
}


STATIC_HX_DEFINE_DYNAMIC_FUNC0(Sys_obj,environment,return )

Dynamic Sys_obj::get_env;

Dynamic Sys_obj::put_env;

Dynamic Sys_obj::_sleep;

Dynamic Sys_obj::set_time_locale;

Dynamic Sys_obj::get_cwd;

Dynamic Sys_obj::set_cwd;

Dynamic Sys_obj::sys_string;

Dynamic Sys_obj::sys_command;

Dynamic Sys_obj::sys_exit;

Dynamic Sys_obj::sys_time;

Dynamic Sys_obj::sys_cpu_time;

Dynamic Sys_obj::sys_exe_path;

Dynamic Sys_obj::sys_env;

Dynamic Sys_obj::file_stdin;

Dynamic Sys_obj::file_stdout;

Dynamic Sys_obj::file_stderr;

Dynamic Sys_obj::getch;


Sys_obj::Sys_obj()
{
}

void Sys_obj::__Mark(HX_MARK_PARAMS)
{
	HX_MARK_BEGIN_CLASS(Sys);
	HX_MARK_END_CLASS();
}

void Sys_obj::__Visit(HX_VISIT_PARAMS)
{
}

Dynamic Sys_obj::__Field(const ::String &inName,bool inCallProp)
{
	switch(inName.length) {
	case 4:
		if (HX_FIELD_EQ(inName,"args") ) { return args_dyn(); }
		if (HX_FIELD_EQ(inName,"exit") ) { return exit_dyn(); }
		if (HX_FIELD_EQ(inName,"time") ) { return time_dyn(); }
		break;
	case 5:
		if (HX_FIELD_EQ(inName,"print") ) { return print_dyn(); }
		if (HX_FIELD_EQ(inName,"stdin") ) { return _stdin_dyn(); }
		if (HX_FIELD_EQ(inName,"sleep") ) { return sleep_dyn(); }
		if (HX_FIELD_EQ(inName,"getch") ) { return getch; }
		break;
	case 6:
		if (HX_FIELD_EQ(inName,"stdout") ) { return _stdout_dyn(); }
		if (HX_FIELD_EQ(inName,"stderr") ) { return _stderr_dyn(); }
		if (HX_FIELD_EQ(inName,"getEnv") ) { return getEnv_dyn(); }
		if (HX_FIELD_EQ(inName,"putEnv") ) { return putEnv_dyn(); }
		if (HX_FIELD_EQ(inName,"getCwd") ) { return getCwd_dyn(); }
		if (HX_FIELD_EQ(inName,"setCwd") ) { return setCwd_dyn(); }
		if (HX_FIELD_EQ(inName,"_sleep") ) { return _sleep; }
		break;
	case 7:
		if (HX_FIELD_EQ(inName,"println") ) { return println_dyn(); }
		if (HX_FIELD_EQ(inName,"getChar") ) { return getChar_dyn(); }
		if (HX_FIELD_EQ(inName,"command") ) { return command_dyn(); }
		if (HX_FIELD_EQ(inName,"cpuTime") ) { return cpuTime_dyn(); }
		if (HX_FIELD_EQ(inName,"get_env") ) { return get_env; }
		if (HX_FIELD_EQ(inName,"put_env") ) { return put_env; }
		if (HX_FIELD_EQ(inName,"get_cwd") ) { return get_cwd; }
		if (HX_FIELD_EQ(inName,"set_cwd") ) { return set_cwd; }
		if (HX_FIELD_EQ(inName,"sys_env") ) { return sys_env; }
		break;
	case 8:
		if (HX_FIELD_EQ(inName,"sys_exit") ) { return sys_exit; }
		if (HX_FIELD_EQ(inName,"sys_time") ) { return sys_time; }
		break;
	case 10:
		if (HX_FIELD_EQ(inName,"systemName") ) { return systemName_dyn(); }
		if (HX_FIELD_EQ(inName,"sys_string") ) { return sys_string; }
		if (HX_FIELD_EQ(inName,"file_stdin") ) { return file_stdin; }
		break;
	case 11:
		if (HX_FIELD_EQ(inName,"environment") ) { return environment_dyn(); }
		if (HX_FIELD_EQ(inName,"sys_command") ) { return sys_command; }
		if (HX_FIELD_EQ(inName,"file_stdout") ) { return file_stdout; }
		if (HX_FIELD_EQ(inName,"file_stderr") ) { return file_stderr; }
		break;
	case 12:
		if (HX_FIELD_EQ(inName,"sys_cpu_time") ) { return sys_cpu_time; }
		if (HX_FIELD_EQ(inName,"sys_exe_path") ) { return sys_exe_path; }
		break;
	case 13:
		if (HX_FIELD_EQ(inName,"setTimeLocale") ) { return setTimeLocale_dyn(); }
		break;
	case 14:
		if (HX_FIELD_EQ(inName,"escapeArgument") ) { return escapeArgument_dyn(); }
		if (HX_FIELD_EQ(inName,"executablePath") ) { return executablePath_dyn(); }
		break;
	case 15:
		if (HX_FIELD_EQ(inName,"set_time_locale") ) { return set_time_locale; }
	}
	return super::__Field(inName,inCallProp);
}

Dynamic Sys_obj::__SetField(const ::String &inName,const Dynamic &inValue,bool inCallProp)
{
	switch(inName.length) {
	case 5:
		if (HX_FIELD_EQ(inName,"getch") ) { getch=inValue.Cast< Dynamic >(); return inValue; }
		break;
	case 6:
		if (HX_FIELD_EQ(inName,"_sleep") ) { _sleep=inValue.Cast< Dynamic >(); return inValue; }
		break;
	case 7:
		if (HX_FIELD_EQ(inName,"get_env") ) { get_env=inValue.Cast< Dynamic >(); return inValue; }
		if (HX_FIELD_EQ(inName,"put_env") ) { put_env=inValue.Cast< Dynamic >(); return inValue; }
		if (HX_FIELD_EQ(inName,"get_cwd") ) { get_cwd=inValue.Cast< Dynamic >(); return inValue; }
		if (HX_FIELD_EQ(inName,"set_cwd") ) { set_cwd=inValue.Cast< Dynamic >(); return inValue; }
		if (HX_FIELD_EQ(inName,"sys_env") ) { sys_env=inValue.Cast< Dynamic >(); return inValue; }
		break;
	case 8:
		if (HX_FIELD_EQ(inName,"sys_exit") ) { sys_exit=inValue.Cast< Dynamic >(); return inValue; }
		if (HX_FIELD_EQ(inName,"sys_time") ) { sys_time=inValue.Cast< Dynamic >(); return inValue; }
		break;
	case 10:
		if (HX_FIELD_EQ(inName,"sys_string") ) { sys_string=inValue.Cast< Dynamic >(); return inValue; }
		if (HX_FIELD_EQ(inName,"file_stdin") ) { file_stdin=inValue.Cast< Dynamic >(); return inValue; }
		break;
	case 11:
		if (HX_FIELD_EQ(inName,"sys_command") ) { sys_command=inValue.Cast< Dynamic >(); return inValue; }
		if (HX_FIELD_EQ(inName,"file_stdout") ) { file_stdout=inValue.Cast< Dynamic >(); return inValue; }
		if (HX_FIELD_EQ(inName,"file_stderr") ) { file_stderr=inValue.Cast< Dynamic >(); return inValue; }
		break;
	case 12:
		if (HX_FIELD_EQ(inName,"sys_cpu_time") ) { sys_cpu_time=inValue.Cast< Dynamic >(); return inValue; }
		if (HX_FIELD_EQ(inName,"sys_exe_path") ) { sys_exe_path=inValue.Cast< Dynamic >(); return inValue; }
		break;
	case 15:
		if (HX_FIELD_EQ(inName,"set_time_locale") ) { set_time_locale=inValue.Cast< Dynamic >(); return inValue; }
	}
	return super::__SetField(inName,inValue,inCallProp);
}

void Sys_obj::__GetFields(Array< ::String> &outFields)
{
	super::__GetFields(outFields);
};

static ::String sStaticFields[] = {
	HX_CSTRING("print"),
	HX_CSTRING("println"),
	HX_CSTRING("stdin"),
	HX_CSTRING("stdout"),
	HX_CSTRING("stderr"),
	HX_CSTRING("getChar"),
	HX_CSTRING("args"),
	HX_CSTRING("getEnv"),
	HX_CSTRING("putEnv"),
	HX_CSTRING("sleep"),
	HX_CSTRING("setTimeLocale"),
	HX_CSTRING("getCwd"),
	HX_CSTRING("setCwd"),
	HX_CSTRING("systemName"),
	HX_CSTRING("escapeArgument"),
	HX_CSTRING("command"),
	HX_CSTRING("exit"),
	HX_CSTRING("time"),
	HX_CSTRING("cpuTime"),
	HX_CSTRING("executablePath"),
	HX_CSTRING("environment"),
	HX_CSTRING("get_env"),
	HX_CSTRING("put_env"),
	HX_CSTRING("_sleep"),
	HX_CSTRING("set_time_locale"),
	HX_CSTRING("get_cwd"),
	HX_CSTRING("set_cwd"),
	HX_CSTRING("sys_string"),
	HX_CSTRING("sys_command"),
	HX_CSTRING("sys_exit"),
	HX_CSTRING("sys_time"),
	HX_CSTRING("sys_cpu_time"),
	HX_CSTRING("sys_exe_path"),
	HX_CSTRING("sys_env"),
	HX_CSTRING("file_stdin"),
	HX_CSTRING("file_stdout"),
	HX_CSTRING("file_stderr"),
	HX_CSTRING("getch"),
	String(null()) };

static ::String sMemberFields[] = {
	String(null()) };

static void sMarkStatics(HX_MARK_PARAMS) {
	HX_MARK_MEMBER_NAME(Sys_obj::__mClass,"__mClass");
	HX_MARK_MEMBER_NAME(Sys_obj::get_env,"get_env");
	HX_MARK_MEMBER_NAME(Sys_obj::put_env,"put_env");
	HX_MARK_MEMBER_NAME(Sys_obj::_sleep,"_sleep");
	HX_MARK_MEMBER_NAME(Sys_obj::set_time_locale,"set_time_locale");
	HX_MARK_MEMBER_NAME(Sys_obj::get_cwd,"get_cwd");
	HX_MARK_MEMBER_NAME(Sys_obj::set_cwd,"set_cwd");
	HX_MARK_MEMBER_NAME(Sys_obj::sys_string,"sys_string");
	HX_MARK_MEMBER_NAME(Sys_obj::sys_command,"sys_command");
	HX_MARK_MEMBER_NAME(Sys_obj::sys_exit,"sys_exit");
	HX_MARK_MEMBER_NAME(Sys_obj::sys_time,"sys_time");
	HX_MARK_MEMBER_NAME(Sys_obj::sys_cpu_time,"sys_cpu_time");
	HX_MARK_MEMBER_NAME(Sys_obj::sys_exe_path,"sys_exe_path");
	HX_MARK_MEMBER_NAME(Sys_obj::sys_env,"sys_env");
	HX_MARK_MEMBER_NAME(Sys_obj::file_stdin,"file_stdin");
	HX_MARK_MEMBER_NAME(Sys_obj::file_stdout,"file_stdout");
	HX_MARK_MEMBER_NAME(Sys_obj::file_stderr,"file_stderr");
	HX_MARK_MEMBER_NAME(Sys_obj::getch,"getch");
};

static void sVisitStatics(HX_VISIT_PARAMS) {
	HX_VISIT_MEMBER_NAME(Sys_obj::__mClass,"__mClass");
	HX_VISIT_MEMBER_NAME(Sys_obj::get_env,"get_env");
	HX_VISIT_MEMBER_NAME(Sys_obj::put_env,"put_env");
	HX_VISIT_MEMBER_NAME(Sys_obj::_sleep,"_sleep");
	HX_VISIT_MEMBER_NAME(Sys_obj::set_time_locale,"set_time_locale");
	HX_VISIT_MEMBER_NAME(Sys_obj::get_cwd,"get_cwd");
	HX_VISIT_MEMBER_NAME(Sys_obj::set_cwd,"set_cwd");
	HX_VISIT_MEMBER_NAME(Sys_obj::sys_string,"sys_string");
	HX_VISIT_MEMBER_NAME(Sys_obj::sys_command,"sys_command");
	HX_VISIT_MEMBER_NAME(Sys_obj::sys_exit,"sys_exit");
	HX_VISIT_MEMBER_NAME(Sys_obj::sys_time,"sys_time");
	HX_VISIT_MEMBER_NAME(Sys_obj::sys_cpu_time,"sys_cpu_time");
	HX_VISIT_MEMBER_NAME(Sys_obj::sys_exe_path,"sys_exe_path");
	HX_VISIT_MEMBER_NAME(Sys_obj::sys_env,"sys_env");
	HX_VISIT_MEMBER_NAME(Sys_obj::file_stdin,"file_stdin");
	HX_VISIT_MEMBER_NAME(Sys_obj::file_stdout,"file_stdout");
	HX_VISIT_MEMBER_NAME(Sys_obj::file_stderr,"file_stderr");
	HX_VISIT_MEMBER_NAME(Sys_obj::getch,"getch");
};

Class Sys_obj::__mClass;

void Sys_obj::__register()
{
	Static(__mClass) = hx::RegisterClass(HX_CSTRING("Sys"), hx::TCanCast< Sys_obj> ,sStaticFields,sMemberFields,
	&__CreateEmpty, &__Create,
	&super::__SGetClass(), 0, sMarkStatics, sVisitStatics);
}

void Sys_obj::__boot()
{
	get_env= ::cpp::Lib_obj::load(HX_CSTRING("std"),HX_CSTRING("get_env"),(int)1);
	put_env= ::cpp::Lib_obj::load(HX_CSTRING("std"),HX_CSTRING("put_env"),(int)2);
	_sleep= ::cpp::Lib_obj::load(HX_CSTRING("std"),HX_CSTRING("sys_sleep"),(int)1);
	set_time_locale= ::cpp::Lib_obj::load(HX_CSTRING("std"),HX_CSTRING("set_time_locale"),(int)1);
	get_cwd= ::cpp::Lib_obj::load(HX_CSTRING("std"),HX_CSTRING("get_cwd"),(int)0);
	set_cwd= ::cpp::Lib_obj::load(HX_CSTRING("std"),HX_CSTRING("set_cwd"),(int)1);
	sys_string= ::cpp::Lib_obj::load(HX_CSTRING("std"),HX_CSTRING("sys_string"),(int)0);
	sys_command= ::cpp::Lib_obj::load(HX_CSTRING("std"),HX_CSTRING("sys_command"),(int)1);
	sys_exit= ::cpp::Lib_obj::load(HX_CSTRING("std"),HX_CSTRING("sys_exit"),(int)1);
	sys_time= ::cpp::Lib_obj::load(HX_CSTRING("std"),HX_CSTRING("sys_time"),(int)0);
	sys_cpu_time= ::cpp::Lib_obj::load(HX_CSTRING("std"),HX_CSTRING("sys_cpu_time"),(int)0);
	sys_exe_path= ::cpp::Lib_obj::load(HX_CSTRING("std"),HX_CSTRING("sys_exe_path"),(int)0);
	sys_env= ::cpp::Lib_obj::load(HX_CSTRING("std"),HX_CSTRING("sys_env"),(int)0);
	file_stdin= ::cpp::Lib_obj::load(HX_CSTRING("std"),HX_CSTRING("file_stdin"),(int)0);
	file_stdout= ::cpp::Lib_obj::load(HX_CSTRING("std"),HX_CSTRING("file_stdout"),(int)0);
	file_stderr= ::cpp::Lib_obj::load(HX_CSTRING("std"),HX_CSTRING("file_stderr"),(int)0);
	getch= ::cpp::Lib_obj::load(HX_CSTRING("std"),HX_CSTRING("sys_getch"),(int)1);
}

