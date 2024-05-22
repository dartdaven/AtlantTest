// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Atlant : ModuleRules
{
	public Atlant(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
