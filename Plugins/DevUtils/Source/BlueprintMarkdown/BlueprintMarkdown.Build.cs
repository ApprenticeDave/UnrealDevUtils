using System.IO;
using UnrealBuildTool;
using System.Diagnostics;
using System;
public class BlueprintMarkdown : ModuleRules
{
    private string ThirdPartyPath
    {
        get { return Path.GetFullPath(Path.Combine(PluginDirectory, "ThirdParty")); }
    }

    private string CMakePath
    {
        get
        {
            string path = @"C:\Program Files\Microsoft Visual Studio\2022\Professional\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin";
            
            return path;
        }
    }
    private string CMarkPath
    {
        get { return Path.Combine(ThirdPartyPath, "cmark"); }
    }

    private bool DownloadCmark()
    {
        try
        {
            if (!Directory.Exists(CMarkPath))
            {
                Directory.CreateDirectory(CMarkPath);
            }

            // Clone cmark if it doesn't exist
            if (!File.Exists(Path.Combine(CMarkPath, "CMakeLists.txt")))
            {
                Process.Start(new ProcessStartInfo
                {
                    FileName = "git",
                    Arguments = "clone https://github.com/commonmark/cmark.git \"" + CMarkPath + "\"",
                    UseShellExecute = false,
                    RedirectStandardOutput = true,
                    CreateNoWindow = true
                }).WaitForExit();
            }
            Console.WriteLine("Downloaded cmark");
            return true;
        }
        catch (Exception e)
        {
            Console.WriteLine("Failed to download cmark: " + e.Message);
            return false;
        }

    }


    private bool BuildCMark()
    {
        try
        {
            string BuildPath = Path.Combine(CMarkPath, "build");
            if (!Directory.Exists(BuildPath))
            {
                Directory.CreateDirectory(BuildPath);
            }

            // Find Visual Studio CMake
            string ProgramFiles = Environment.GetFolderPath(Environment.SpecialFolder.ProgramFiles);
            string CMakePath =
                $@"C:\Program Files\Microsoft Visual Studio\2022\Professional\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe";

            if (!File.Exists(CMakePath))
            {
                throw new Exception($"CMake not found at: {CMakePath}");
            }
            else
            {
                Console.WriteLine("Found CMake at: " + CMakePath);
            }

// cmake -S . -B build  # optionally: -DCMAKE_INSTALL_PREFIX=path
// cmake --build build  # executable will be created as build/src/cmark
// ctest --test-dir build
// cmake --install build

            // Configure CMake
            Process.Start(new ProcessStartInfo
            {
                FileName = $"{CMakePath}",
                Arguments = $"-S . -B build",
                WorkingDirectory = BuildPath,
                UseShellExecute = false,
                RedirectStandardOutput = true,
                CreateNoWindow = true
            }).WaitForExit();

            // Build using CMake
            Process.Start(new ProcessStartInfo
            {
                FileName = $"{CMakePath}",
                Arguments = "--build build",
                WorkingDirectory = BuildPath,
                UseShellExecute = false,
                RedirectStandardOutput = true,
                CreateNoWindow = true
            }).WaitForExit();

            Console.WriteLine("Built cmark successfully");
            return true;
        }
        catch (Exception e)
        {
            Console.WriteLine("Failed to build cmark: " + e.Message);
            return false;
        }

    }
    
    public BlueprintMarkdown(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        
        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core", 
                "CoreUObject", 
                "Engine", 
                "Slate", 
                "SlateCore",
                "GraphEditor",
                "BlueprintGraph",
                "UnrealEd",
                "EditorStyle",
                "Kismet",
                "UnrealEd",
                "Projects",
                "InputCore",
                "EditorStyle",
                "PropertyEditor",
                "KismetCompiler"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore"
            }
        );

        if (DownloadCmark())
        {
            BuildCMark();
            
            PublicIncludePaths.Add(Path.Combine(CMarkPath, "src"));
            PublicIncludePaths.Add(Path.Combine(Path.Combine(CMarkPath, "build")
                , "src"));
        
            // Add the library path
            PublicSystemLibraryPaths.Add(Path.Combine(Path.Combine(CMarkPath, "build")
                , "src"));
        
            
            PublicAdditionalLibraries.Add(Path.Combine(Path.Combine(CMarkPath, "build")
                    , "src", "Debug", "cmark.lib"));
            

        }
        else
        {
            Console.WriteLine("Failed to download or setup cmark. The module may not function correctly.");
        }
        

        
        PublicIncludePaths.Add(Path.Combine(ModuleDirectory,"Public"));
        PrivateIncludePaths.Add(Path.Combine(ModuleDirectory,"Private"));
    }
}