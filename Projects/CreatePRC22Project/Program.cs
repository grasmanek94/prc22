using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Resources;

namespace CreatePRC22Project
{
	class Program
	{
		static void Main(string[] args)
		{
			bool good = false;

			string currentPath = System.IO.Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().Location);

			string projectName = "";			
			string projectPath = "";

			while (!good)
			{
				Console.WriteLine("New Project Name:");
				projectName = Console.ReadLine().Replace(" ", "").Replace("\t", "");			
				try
				{
					projectPath = currentPath + "\\" + projectName + "\\";
					Directory.CreateDirectory(projectPath);
					good = true;
				}
				catch (Exception ex)
				{
					Console.WriteLine("Invalid Project Name: " + ex.Message);
				}
			}

			try
			{
				File.WriteAllText(projectPath + "BUILD.BAT", CreatePRC22Project.Properties.Resources.BUILD_BAT);
				File.WriteAllText(projectPath + "CLEAN.BAT", CreatePRC22Project.Properties.Resources.CLEAN_BAT);
				File.WriteAllText(projectPath + "CYGWIN.BAT", CreatePRC22Project.Properties.Resources.CYGWIN_BAT);
				File.WriteAllText(projectPath + "DEBUG.BAT", CreatePRC22Project.Properties.Resources.DEBUG_BAT);
				File.WriteAllText(projectPath + "REBUILD.BAT", CreatePRC22Project.Properties.Resources.REBUILD_BAT);
				File.WriteAllText(projectPath + "RUN.BAT", CreatePRC22Project.Properties.Resources.RUN_BAT);
				File.WriteAllText(projectPath + "RUNTEST.BAT", CreatePRC22Project.Properties.Resources.RUNTEST_BAT);
				File.WriteAllText(projectPath + "makefile", CreatePRC22Project.Properties.Resources.makefile);

				File.WriteAllText(projectPath + "main.c", CreatePRC22Project.Properties.Resources.main_c.Replace("PROJECTNAME", projectName));
				File.WriteAllText(projectPath + "main.h", CreatePRC22Project.Properties.Resources.main_h.Replace("PROJECTNAME", projectName));
				File.WriteAllText(projectPath + projectName + ".c", CreatePRC22Project.Properties.Resources.PROJECTNAME_c.Replace("PROJECTNAME", projectName));
				File.WriteAllText(projectPath + projectName + ".h", CreatePRC22Project.Properties.Resources.PROJECTNAME_h.Replace("PROJECTNAME", projectName));
				File.WriteAllText(projectPath + projectName + "_test.c", CreatePRC22Project.Properties.Resources.PROJECTNAME_test_c.Replace("PROJECTNAME", projectName));
				File.WriteAllText(projectPath + projectName + "_test.h", CreatePRC22Project.Properties.Resources.PROJECTNAME_test_h.Replace("PROJECTNAME", projectName));
				File.WriteAllText(projectPath + projectName + ".sln", CreatePRC22Project.Properties.Resources.PROJECTNAME_sln.Replace("PROJECTNAME", projectName));
				File.WriteAllText(projectPath + projectName + ".vcxproj", CreatePRC22Project.Properties.Resources.PROJECTNAME_vcxproj.Replace("PROJECTNAME", projectName));
				File.WriteAllText(projectPath + projectName + ".vcxproj.filters", CreatePRC22Project.Properties.Resources.PROJECTNAME_vcxproj_filters.Replace("PROJECTNAME", projectName));
			}
			catch (Exception ex)
			{
				Console.WriteLine("Project Creation Failed with message: " + ex.Message);
				Console.ReadLine();
			}
		}
	}
}
