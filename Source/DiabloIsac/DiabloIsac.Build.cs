// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DiabloIsac : ModuleRules
{
	public DiabloIsac(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "NavigationSystem", "AIModule", "Niagara", "EnhancedInput", "GameplayTasks","Slate","SlateCore" });
    }
}
