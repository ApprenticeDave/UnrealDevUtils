using UnrealBuildTool;
using System.IO;
public class BlueprintMarkdown : ModuleRules
{
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
        
        PublicIncludePaths.Add(Path.Combine(ModuleDirectory,"Public"));
        PrivateIncludePaths.Add(Path.Combine(ModuleDirectory,"Private"));
    }
}