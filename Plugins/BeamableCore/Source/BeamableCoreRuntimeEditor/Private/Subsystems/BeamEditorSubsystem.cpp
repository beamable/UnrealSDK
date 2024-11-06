// Fill out your copyright notice in the Description page of Project Settings.

#include "Subsystems/BeamEditorSubsystem.h"

#include "Subsystems/BeamEditor.h"
#include "BeamLogging.h"

void UBeamEditorSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	RequestTracker = GEngine->GetEngineSubsystem<UBeamRequestTracker>();
	Editor = Cast<UBeamEditor>(Collection.InitializeDependency(UBeamEditor::StaticClass()));
}

void UBeamEditorSubsystem::Deinitialize()
{
}

FBeamOperationHandle UBeamEditorSubsystem::InitializeWhenEditorReady()
{
	UE_LOG(LogBeamEditor, Display, TEXT("Editor Subsystem %s - Initializing after Unreal Editor is ready"), *GetName())

	// By default, just return an empty completed operation
	const auto Handle = RequestTracker->BeginOperation({Editor->GetMainEditorSlot()}, GetName(), {});
	RequestTracker->TriggerOperationSuccess(Handle, {});
	return Handle;
}

FBeamOperationHandle UBeamEditorSubsystem::PrepareForRealmChange(FBeamRealmHandle CurrRealm, FBeamRealmHandle NewRealm)
{
	UE_LOG(LogBeamEditor, Display, TEXT("Editor Subsystem %s - Preparing for Realm Change"), *GetName())

	// By default, just return an empty completed operation
	const auto Handle = RequestTracker->BeginOperation({Editor->GetMainEditorSlot()}, GetName(), {});
	RequestTracker->TriggerOperationSuccess(Handle, {});
	return Handle;
}

FBeamOperationHandle UBeamEditorSubsystem::InitializeRealm(FBeamRealmHandle NewRealm)
{
	UE_LOG(LogBeamEditor, Display, TEXT("Editor Subsystem %s - Preparing Editor to work with new Realm"), *GetName())

	// By default, just return an empty completed operation
	const auto Handle = RequestTracker->BeginOperation({Editor->GetMainEditorSlot()}, GetName(), {});
	RequestTracker->TriggerOperationSuccess(Handle, {});

	return Handle;
}

FBeamOperationHandle UBeamEditorSubsystem::OnRealmInitialized(FBeamRealmHandle NewRealm)
{
	UE_LOG(LogBeamEditor, Display, TEXT("Editor Subsystem %s - Initializing state from new realm"), *GetName())

	// By default, just return an empty completed operation
	const auto Handle = RequestTracker->BeginOperation({Editor->GetMainEditorSlot()}, GetName(), {});
	RequestTracker->TriggerOperationSuccess(Handle, {});

	return Handle;
}

void UBeamEditorSubsystem::OnReady()
{
	UE_LOG(LogBeamEditor, Display, TEXT("Editor Subsystem %s - Editor System Ready for use With Realm"), *GetName())
}

void UBeamEditorSubsystem::OnSignOut()
{
	UE_LOG(LogBeamEditor, Display, TEXT("Editor Subsystem %s - Sign Out Detected"), *GetName())
}
