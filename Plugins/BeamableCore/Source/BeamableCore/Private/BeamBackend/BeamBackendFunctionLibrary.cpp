// Fill out your copyright notice in the Description page of Project Settings.


#include "BeamBackend/BeamBackendFunctionLibrary.h"

#include "BeamBackend/BeamBackend.h"

bool UBeamBackendFunctionLibrary::WasSuccess(const FBeamRequestContext& Context)
{
	return Context.ResponseCode == 200;
}

bool UBeamBackendFunctionLibrary::WasError(const FBeamRequestContext& Context)
{
	return Context.ResponseCode != -1 && Context.ResponseCode != 200;
}

void UBeamBackendFunctionLibrary::CancelRequest(const FBeamRequestContext& Context)
{
	return UBeamBackend::GetSelf()->CancelRequest(Context.RequestId);
}

bool UBeamBackendFunctionLibrary::IsRequestCancelled(const FBeamRequestContext& Context)
{
	return UBeamBackend::GetSelf()->IsRequestCancelled(Context.RequestId);
}

int UBeamBackendFunctionLibrary::GetRequestFailureCount(const FBeamRequestContext& Context)
{
	return UBeamBackend::GetSelf()->GetRequestFailureCount(Context.RequestId);
}
