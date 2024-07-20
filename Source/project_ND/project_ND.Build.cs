// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class project_ND : ModuleRules
{
	public project_ND(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput",
			"AIModule", "NavigationSystem"
		});
	}
}
