// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Assignment6 : ModuleRules
{
	public Assignment6(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
