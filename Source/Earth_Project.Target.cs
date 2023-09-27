// Earth_Project, All rights reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class Earth_ProjectTarget : TargetRules
{
	public Earth_ProjectTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V4;
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;

        ExtraModuleNames.AddRange( new string[] { "Earth_Project" } );
	}
}
