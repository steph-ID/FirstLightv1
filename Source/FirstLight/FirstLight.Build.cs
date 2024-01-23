// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FirstLight : ModuleRules
{
	public FirstLight(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"HeadMountedDisplay", 
			"EnhancedInput",
			"MovieScene",
			"LevelSequence"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {
			"GameplayTags",
			"GameplayAbilities",
			"GameplayTasks", 
			"AITestSuite", 
			"Niagara"
		});
	}
}
