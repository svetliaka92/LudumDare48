// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DeeperAndDeeper : ModuleRules
{
	public DeeperAndDeeper(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG" });
	}
}
