using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Resources;

namespace CreateRP6Project
{
	class Program
	{
		static void Main(string[] args)
		{
			bool good = false;

			string currentPath = System.IO.Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().Location);

			string projectName = "";			
			string projectPath = "";
			string projectPathBase = "";
			string projectPathCommon = "";
			string projectPathControl = "";

			while (!good)
			{
				Console.WriteLine("New Project Name:");
				projectName = Console.ReadLine().Replace(" ", "").Replace("\t", "");			
				try
				{
					projectPath = currentPath + "\\" + projectName + "\\";
					projectPathBase = projectPath + "base\\";
					projectPathCommon = projectPath + "common\\";
					projectPathControl = projectPath + "control\\";

					Directory.CreateDirectory(projectPath);
					Directory.CreateDirectory(projectPathBase);
					Directory.CreateDirectory(projectPathCommon);
					Directory.CreateDirectory(projectPathControl);

					good = true;
				}
				catch (Exception ex)
				{
					Console.WriteLine("Invalid Project Name: " + ex.Message);
				}
			}

			try
			{
				File.WriteAllText(projectPathBase + "BUILDUPLOAD.BAT", CreateRP6Project.Properties.Resources.BUILDUPLOAD_bat);
				File.WriteAllText(projectPathBase + "makefile", CreateRP6Project.Properties.Resources.base_makefile);
				File.WriteAllText(projectPathBase + "base.c", CreateRP6Project.Properties.Resources.base_c);
				File.WriteAllText(projectPathBase + "base.h", CreateRP6Project.Properties.Resources.base_h);

				File.WriteAllText(projectPathControl + "BUILDUPLOAD.BAT", CreateRP6Project.Properties.Resources.BUILDUPLOAD_bat);
				File.WriteAllText(projectPathControl + "makefile", CreateRP6Project.Properties.Resources.control_makefile);
				File.WriteAllText(projectPathControl + "control.c", CreateRP6Project.Properties.Resources.control_c);
				File.WriteAllText(projectPathControl + "control.h", CreateRP6Project.Properties.Resources.control_h);

				File.WriteAllText(projectPathCommon + "someCommonLib.c", CreateRP6Project.Properties.Resources.common_someCommonLib_c);
				File.WriteAllText(projectPathCommon + "someCommonLib.h", CreateRP6Project.Properties.Resources.common_someCommonLib_h);

				File.WriteAllText(projectPath + projectName + ".sln", CreateRP6Project.Properties.Resources.PROJECTNAME_sln.Replace("PROJECTNAME", projectName));
				File.WriteAllText(projectPath + projectName + ".vcxproj", CreateRP6Project.Properties.Resources.PROJECTNAME_vcxproj.Replace("PROJECTNAME", projectName));
				File.WriteAllText(projectPath + projectName + ".vcxproj.filters", CreateRP6Project.Properties.Resources.PROJECTNAME_vcxproj_filters.Replace("PROJECTNAME", projectName));
			}
			catch (Exception ex)
			{
				Console.WriteLine("Project Creation Failed with message: " + ex.Message);
				Console.ReadLine();
			}
		}
	}
}
