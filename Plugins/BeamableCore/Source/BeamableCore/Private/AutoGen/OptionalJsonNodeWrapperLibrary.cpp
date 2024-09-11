
#include "BeamableCore/Public/AutoGen/OptionalJsonNodeWrapperLibrary.h"

#include "CoreMinimal.h"


FString UOptionalJsonNodeWrapperLibrary::OptionalJsonNodeWrapperToJsonString(const UOptionalJsonNodeWrapper* Serializable, const bool Pretty)
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

UOptionalJsonNodeWrapper* UOptionalJsonNodeWrapperLibrary::Make(FOptionalString Node, UObject* Outer)
{
	auto Serializable = NewObject<UOptionalJsonNodeWrapper>(Outer);
	Serializable->Node = Node;
	
	return Serializable;
}

void UOptionalJsonNodeWrapperLibrary::Break(const UOptionalJsonNodeWrapper* Serializable, FOptionalString& Node)
{
	Node = Serializable->Node;
		
}

