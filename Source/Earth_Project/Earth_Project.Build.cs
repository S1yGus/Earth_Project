// Earth_Project, All rights reserved.

using UnrealBuildTool;

public class Earth_Project : ModuleRules
{
    public Earth_Project(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "SlateCore" });

        PrivateDependencyModuleNames.AddRange(new string[] { });
    }
}
