﻿//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:4.0.30319.0
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace CreatePRC22Project.Properties {
    using System;
    
    
    /// <summary>
    ///   A strongly-typed resource class, for looking up localized strings, etc.
    /// </summary>
    // This class was auto-generated by the StronglyTypedResourceBuilder
    // class via a tool like ResGen or Visual Studio.
    // To add or remove a member, edit your .ResX file then rerun ResGen
    // with the /str option, or rebuild your VS project.
    [global::System.CodeDom.Compiler.GeneratedCodeAttribute("System.Resources.Tools.StronglyTypedResourceBuilder", "4.0.0.0")]
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute()]
    [global::System.Runtime.CompilerServices.CompilerGeneratedAttribute()]
    internal class Resources {
        
        private static global::System.Resources.ResourceManager resourceMan;
        
        private static global::System.Globalization.CultureInfo resourceCulture;
        
        [global::System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1811:AvoidUncalledPrivateCode")]
        internal Resources() {
        }
        
        /// <summary>
        ///   Returns the cached ResourceManager instance used by this class.
        /// </summary>
        [global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]
        internal static global::System.Resources.ResourceManager ResourceManager {
            get {
                if (object.ReferenceEquals(resourceMan, null)) {
                    global::System.Resources.ResourceManager temp = new global::System.Resources.ResourceManager("CreatePRC22Project.Properties.Resources", typeof(Resources).Assembly);
                    resourceMan = temp;
                }
                return resourceMan;
            }
        }
        
        /// <summary>
        ///   Overrides the current thread's CurrentUICulture property for all
        ///   resource lookups using this strongly typed resource class.
        /// </summary>
        [global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]
        internal static global::System.Globalization.CultureInfo Culture {
            get {
                return resourceCulture;
            }
            set {
                resourceCulture = value;
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to @echo off
        ///cd /D &quot;%~dp0&quot;
        ///set PATH=%CYGWIN64%\bin;%PATH%
        ///make.
        /// </summary>
        internal static string BUILD_BAT {
            get {
                return ResourceManager.GetString("BUILD_BAT", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to @echo off
        ///cd /D &quot;%~dp0&quot;
        ///set PATH=%CYGWIN64%\bin;%PATH%
        ///make clean.
        /// </summary>
        internal static string CLEAN_BAT {
            get {
                return ResourceManager.GetString("CLEAN_BAT", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to @echo off
        ///cd /D &quot;%~dp0&quot;
        ///set PATH=%CYGWIN64%\usr\bin;%CYGWIN64%\bin;%CYGWIN64%\usr\sbin;%CYGWIN64%\usr\local\bin;
        ///start &quot;&quot; &quot;%CYGWIN64%\bin\mintty.exe&quot;.
        /// </summary>
        internal static string CYGWIN_BAT {
            get {
                return ResourceManager.GetString("CYGWIN_BAT", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to @echo off
        ///cd /D &quot;%~dp0&quot;
        ///set PATH=%CYGWIN64%\bin;%PATH%
        ///gdb.
        /// </summary>
        internal static string DEBUG_BAT {
            get {
                return ResourceManager.GetString("DEBUG_BAT", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to /*
        ///	Main PROJECTNAME source file
        ///*/
        ///
        /////Default includes
        ///#include &lt;stdio.h&gt;
        ///
        /////Custom includes
        ///#include &quot;main.h&quot;
        ///#include &quot;PROJECTNAME.h&quot;
        ///
        ///int main(void)
        ///{
        ///	return 0;
        ///}
        ///.
        /// </summary>
        internal static string main_c {
            get {
                return ResourceManager.GetString("main_c", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to /*
        ///	Main header file
        ///*/
        ///
        /////Include Guard
        ///#ifndef main_HEADER
        ///#define main_HEADER
        ///int main(void);
        ///#endif.
        /// </summary>
        internal static string main_h {
            get {
                return ResourceManager.GetString("main_h", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to comma:= ,
        ///empty:=
        ///space:= $(empty) $(empty)
        ///
        ///CYGWIN_BASE=/cygdrive/$(subst \,/,$(subst :,$(empty),$(CYGWIN64)))
        ///PRC22LIBS=$(CYGWIN_BASE)/prc22libs
        ///
        ///mkfile_path := $(subst $(space),$(empty),$(abspath $(lastword $(MAKEFILE_LIST))))
        ///project_name := $(notdir $(patsubst %/,%,$(dir $(mkfile_path))))
        ///
        ///#actual program
        ///RESOURCE_CHECK_FOLDER=$(PRC22LIBS)/ResourceDetector
        ///
        ///INC_DIRS=-I$(RESOURCE_CHECK_FOLDER)
        ///
        ///CFLAGS = -Wall -Werror -pedantic -O2 -std=c99 -g
        ///
        ///TEST_MAIN_SRC = $(project_name)_test.c
        ///
        ///S [rest of string was truncated]&quot;;.
        /// </summary>
        internal static string makefile {
            get {
                return ResourceManager.GetString("makefile", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to /*
        ///	Main PROJECTNAME source file
        ///*/
        ///
        /////Default includes
        ///#include &lt;stdio.h&gt;
        ///
        /////Custom includes
        ///#include &quot;main.h&quot;
        ///#include &quot;PROJECTNAME.h&quot;
        ///.
        /// </summary>
        internal static string PROJECTNAME_c {
            get {
                return ResourceManager.GetString("PROJECTNAME_c", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to /*
        ///	Main PROJECTNAME header file
        ///*/
        ///
        /////Include Guard
        ///#ifndef PROJECTNAME_HEADER
        ///#define PROJECTNAME_HEADER
        ///
        ///#endif.
        /// </summary>
        internal static string PROJECTNAME_h {
            get {
                return ResourceManager.GetString("PROJECTNAME_h", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Microsoft Visual Studio Solution File, Format Version 12.00
        ///VisualStudioVersion = 12.0.31101.0
        ///MinimumVisualStudioVersion = 10.0.40219.1
        ///Project(&quot;{8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942}&quot;) = &quot;PROJECTNAME&quot;, &quot;PROJECTNAME.vcxproj&quot;, &quot;{37A42495-D54F-4BA1-9C69-788A3AFFD401}&quot;
        ///EndProject
        ///Global
        ///	GlobalSection(SolutionConfigurationPlatforms) = preSolution
        ///		Debug|Win32 = Debug|Win32
        ///	EndGlobalSection
        ///	GlobalSection(ProjectConfigurationPlatforms) = postSolution
        ///		{37A42495-D54F-4BA1-9C69-788A3AFFD401}.Debug|W [rest of string was truncated]&quot;;.
        /// </summary>
        internal static string PROJECTNAME_sln {
            get {
                return ResourceManager.GetString("PROJECTNAME_sln", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to /*
        ///	Main PROJECTNAME test file
        ///*/
        ///
        /////Default includes
        ///#include &lt;stdio.h&gt;
        ///
        /////Unit testin includes
        ///#include &lt;unity.h&gt;
        ///
        /////Custom includes
        ///#include &quot;PROJECTNAME.h&quot;
        ///#include &quot;PROJECTNAME_test.h&quot;
        ///
        ///void setUp(void)
        ///{
        ///
        ///}
        ///
        ///void tearDown(void)
        ///{
        ///
        ///}
        ///
        ///int main(void)
        ///{
        ///	UnityBegin();
        ///	//Run tests here
        ///	return UnityEnd();
        ///}
        ///.
        /// </summary>
        internal static string PROJECTNAME_test_c {
            get {
                return ResourceManager.GetString("PROJECTNAME_test_c", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to /*
        ///	Main PROJECTNAME_test header file
        ///*/
        ///
        /////Include Guard
        ///#ifndef PROJECTNAME_test_HEADER
        ///#define PROJECTNAME_test_HEADER
        ///void setUp(void);
        ///void tearDown(void);
        ///int main(void);
        ///#endif.
        /// </summary>
        internal static string PROJECTNAME_test_h {
            get {
                return ResourceManager.GetString("PROJECTNAME_test_h", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to &lt;?xml version=&quot;1.0&quot; encoding=&quot;utf-8&quot;?&gt;
        ///&lt;Project DefaultTargets=&quot;Build&quot; ToolsVersion=&quot;12.0&quot; xmlns=&quot;http://schemas.microsoft.com/developer/msbuild/2003&quot;&gt;
        ///  &lt;ItemGroup Label=&quot;ProjectConfigurations&quot;&gt;
        ///    &lt;ProjectConfiguration Include=&quot;Debug|Win32&quot;&gt;
        ///      &lt;Configuration&gt;Debug&lt;/Configuration&gt;
        ///      &lt;Platform&gt;Win32&lt;/Platform&gt;
        ///    &lt;/ProjectConfiguration&gt;
        ///  &lt;/ItemGroup&gt;
        ///  &lt;ItemGroup&gt;
        ///    &lt;ClInclude Include=&quot;main.h&quot; /&gt;
        ///    &lt;ClInclude Include=&quot;PROJECTNAME.h&quot; /&gt;
        ///    &lt;ClInclude Include=&quot;PROJECTNAME_test.h&quot; /&gt; [rest of string was truncated]&quot;;.
        /// </summary>
        internal static string PROJECTNAME_vcxproj {
            get {
                return ResourceManager.GetString("PROJECTNAME_vcxproj", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to &lt;?xml version=&quot;1.0&quot; encoding=&quot;utf-8&quot;?&gt;
        ///&lt;Project ToolsVersion=&quot;4.0&quot; xmlns=&quot;http://schemas.microsoft.com/developer/msbuild/2003&quot;&gt;
        ///  &lt;ItemGroup&gt;
        ///    &lt;Filter Include=&quot;util&quot;&gt;
        ///      &lt;UniqueIdentifier&gt;{76f63abe-dacf-423a-85f6-56b679a2a892}&lt;/UniqueIdentifier&gt;
        ///    &lt;/Filter&gt;
        ///    &lt;Filter Include=&quot;source&quot;&gt;
        ///      &lt;UniqueIdentifier&gt;{fca16c96-6b2d-4420-8213-b4384f5c0954}&lt;/UniqueIdentifier&gt;
        ///    &lt;/Filter&gt;
        ///  &lt;/ItemGroup&gt;
        ///  &lt;ItemGroup&gt;
        ///    &lt;ClCompile Include=&quot;PROJECTNAME.c&quot;&gt;
        ///      &lt;Filter&gt;source&lt;/Filter&gt;
        ///    &lt;/Cl [rest of string was truncated]&quot;;.
        /// </summary>
        internal static string PROJECTNAME_vcxproj_filters {
            get {
                return ResourceManager.GetString("PROJECTNAME_vcxproj_filters", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to @echo off
        ///cd /D &quot;%~dp0&quot;
        ///set PATH=%CYGWIN64%\bin;%PATH%
        ///make clean
        ///make.
        /// </summary>
        internal static string REBUILD_BAT {
            get {
                return ResourceManager.GetString("REBUILD_BAT", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to @echo off
        ///cd /D &quot;%~dp0&quot;
        ///for /f &quot;delims=\&quot; %%a in (&quot;%~dp0&quot;) do SET executable=&quot;%%~nxa&quot;
        ///set PATH=%CYGWIN64%\usr\bin;%CYGWIN64%\bin;%CYGWIN64%\usr\sbin;%CYGWIN64%\usr\local\bin;
        ///%executable%
        ///echo(
        ///echo Application exitted with code %errorlevel%
        ///pause.
        /// </summary>
        internal static string RUN_BAT {
            get {
                return ResourceManager.GetString("RUN_BAT", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to @echo off
        ///cd /D &quot;%~dp0&quot;
        ///for /f &quot;delims=\&quot; %%a in (&quot;%~dp0&quot;) do SET executable=&quot;%%~nxa_test&quot;
        ///set PATH=%CYGWIN64%\usr\bin;%CYGWIN64%\bin;%CYGWIN64%\usr\sbin;%CYGWIN64%\usr\local\bin;
        ///%executable%
        ///echo(
        ///echo Application exitted with code %errorlevel%
        ///pause.
        /// </summary>
        internal static string RUNTEST_BAT {
            get {
                return ResourceManager.GetString("RUNTEST_BAT", resourceCulture);
            }
        }
    }
}
