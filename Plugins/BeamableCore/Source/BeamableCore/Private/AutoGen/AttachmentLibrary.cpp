
#include "BeamableCore/Public/AutoGen/AttachmentLibrary.h"

#include "CoreMinimal.h"


FString UAttachmentLibrary::AttachmentToJsonString(const UAttachment* Serializable, const bool Pretty)
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

UAttachment* UAttachmentLibrary::Make(int64 Id, UEntitlementGenerator* Wrapped, FString State, FOptionalInt64 Target, UObject* Outer)
{
	auto Serializable = NewObject<UAttachment>(Outer);
	Serializable->Id = Id;
	Serializable->Wrapped = Wrapped;
	Serializable->State = State;
	Serializable->Target = Target;
	
	return Serializable;
}

void UAttachmentLibrary::Break(const UAttachment* Serializable, int64& Id, UEntitlementGenerator*& Wrapped, FString& State, FOptionalInt64& Target)
{
	Id = Serializable->Id;
	Wrapped = Serializable->Wrapped;
	State = Serializable->State;
	Target = Serializable->Target;
		
}

