// Earth_Project, All rights reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class Earth_ProjectEditorTarget : TargetRules
{
	public Earth_ProjectEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "Earth_Project" } );
	}
}
