// Fill out your copyright notice in the Description page of Project Settings.


#include "Serialization/BeamPlainTextResponseBody.h"

void UBeamPlainTextResponseBody::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	Response = ResponseContent;		
}
