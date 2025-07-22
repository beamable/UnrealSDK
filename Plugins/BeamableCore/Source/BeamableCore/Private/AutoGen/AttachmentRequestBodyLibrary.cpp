
#include "BeamableCore/Public/AutoGen/AttachmentRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UAttachmentRequestBodyLibrary::AttachmentRequestBodyToJsonString(const UAttachmentRequestBody* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<TCHAR>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();			
	}
	return Result;
}	

UAttachmentRequestBody* UAttachmentRequestBodyLibrary::Make(FString Symbol, FString Action, FOptionalInt32 Quantity, FOptionalString Specialization, FOptionalInt64 Target, UObject* Outer)
{
	auto Serializable = NewObject<UAttachmentRequestBody>(Outer);
	Serializable->Symbol = Symbol;
	Serializable->Action = Action;
	Serializable->Quantity = Quantity;
	Serializable->Specialization = Specialization;
	Serializable->Target = Target;
	
	return Serializable;
}

void UAttachmentRequestBodyLibrary::Break(const UAttachmentRequestBody* Serializable, FString& Symbol, FString& Action, FOptionalInt32& Quantity, FOptionalString& Specialization, FOptionalInt64& Target)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Symbol = Serializable->Symbol;
		Action = Serializable->Action;
		Quantity = Serializable->Quantity;
		Specialization = Serializable->Specialization;
		Target = Serializable->Target;
	}
		
}

