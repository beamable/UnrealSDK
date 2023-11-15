// Fill out your copyright notice in the Description page of Project Settings.


#include "Runtime/BeamRuntimeSubsystem.h"

#include "BeamLogging.h"

void UBeamRuntimeSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Runtime = Collection.InitializeDependency<UBeamRuntime>();
}

void UBeamRuntimeSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

bool UBeamRuntimeSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	if (IsInBlueprint())
	{
		const auto RuntimeSettings = GetDefault<UBeamRuntimeSettings>();
		for (const auto SubsystemBlueprint : RuntimeSettings->RuntimeSubsystemBlueprints)
		{
			if (this == SubsystemBlueprint->GetDefaultObject())
				return true;
		}

		if (IsRunningDedicatedServer())
		{
			for (const auto SubsystemBlueprint : RuntimeSettings->ServerOnlyRuntimeSubsystemBlueprints)
			{
				if (this == SubsystemBlueprint->GetDefaultObject())
					return true;
			}
		}
		else
		{
			for (const auto SubsystemBlueprint : RuntimeSettings->ClientRuntimeSubsystemBlueprints)
			{
				if (this == SubsystemBlueprint->GetDefaultObject())
					return true;
			}
		}

		return false;
	}

	return true;
}

void UBeamRuntimeSubsystem::InitializeWhenUnrealReady_Implementation(FBeamOperationHandle& ResultOp)
{
	UE_LOG(LogBeamRuntime, Verbose, TEXT("Runtime Subsystem %s - Initializing after GameInstance is ready"), *GetName())

	// By default, just return an empty completed operation
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({}, GetName(), {});
	Runtime->RequestTrackerSystem->TriggerOperationSuccess(Handle, {});
	ResultOp = Handle;
}

void UBeamRuntimeSubsystem::OnBeamableStarting_Implementation(FBeamOperationHandle& ResultOp)
{
	// By default, just return an empty completed operation
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({}, GetName(), {});
	Runtime->RequestTrackerSystem->TriggerOperationSuccess(Handle, {});	
	ResultOp = Handle;
}

void UBeamRuntimeSubsystem::OnFailedUserAuth_Implementation(const FUserSlot& UserSlot)
{
	UE_LOG(LogBeamRuntime, Verbose, TEXT("Runtime Subsystem %s - On Failed Owner User Auth"), *GetName())
}

void UBeamRuntimeSubsystem::OnUserConnectionLost_Implementation(const FUserSlot& UserSlot)
{
	UE_LOG(LogBeamRuntime, Verbose, TEXT("Runtime Subsystem %s - On User Connection Lost"), *GetName())
}

void UBeamRuntimeSubsystem::OnUserSignedIn_Implementation(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const bool bIsOwnerUserAuth, FBeamOperationHandle& ResultOp)
{
	UE_LOG(LogBeamRuntime, Verbose, TEXT("Runtime Subsystem %s - On User Signed In from Slot %s"), *GetName(), *UserSlot.Name)

	// By default, just return an empty completed operation
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({}, GetName(), {});
	Runtime->RequestTrackerSystem->TriggerOperationSuccess(Handle, {});
	ResultOp = Handle;
}

void UBeamRuntimeSubsystem::OnPostUserSignedIn_Implementation(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const bool bIsOwnerUserAuth, FBeamOperationHandle& ResultOp)
{
	UE_LOG(LogBeamRuntime, Verbose, TEXT("Runtime Subsystem %s - On Post User Signed Into Slot %s"), *GetName(), *UserSlot.Name)	

	// By default, just return an empty completed operation
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({}, GetName(), {});
	Runtime->RequestTrackerSystem->TriggerOperationSuccess(Handle, {});
	ResultOp = Handle;
}

void UBeamRuntimeSubsystem::OnUserSignedOut_Implementation(const FUserSlot& UserSlot, const EUserSlotClearedReason Reason, const FBeamRealmUser& BeamRealmUser, FBeamOperationHandle& ResultOp)
{
	UE_LOG(LogBeamRuntime, Verbose, TEXT("Runtime Subsystem %s - On User Signed Out from Slot %s and Reason %s"), *GetName(), *UserSlot.Name,
	       *StaticEnum<EUserSlotClearedReason>()->GetValueAsString(Reason))

	// By default, just return an empty completed operation
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({}, GetName(), {});
	Runtime->RequestTrackerSystem->TriggerOperationSuccess(Handle, {});
	ResultOp = Handle;
}

void UBeamRuntimeSubsystem::OnPostUserSignedOut_Implementation(const FUserSlot& UserSlot, const EUserSlotClearedReason Reason, const FBeamRealmUser& BeamRealmUser, FBeamOperationHandle& ResultOp)
{
	UE_LOG(LogBeamRuntime, Verbose, TEXT("Runtime Subsystem %s - On Post User Signed Out from Slot %s and Reason %s"), *GetName(), *UserSlot.Name,
		   *StaticEnum<EUserSlotClearedReason>()->GetValueAsString(Reason))
	
	// By default, just return an empty completed operation
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({}, GetName(), {});
	Runtime->RequestTrackerSystem->TriggerOperationSuccess(Handle, {});
	ResultOp = Handle;
}


