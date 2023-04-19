
#include "BeamableCore/Public/AutoGen/EmptyRspLibrary.h"

#include "CoreMinimal.h"


FString UEmptyRspLibrary::EmptyRspToJsonString(const UEmptyRsp* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();			
	}
	return Result;
}	

UEmptyRsp* UEmptyRspLibrary::Make(UObject* Outer)
{
	auto Serializable = NewObject<UEmptyRsp>(Outer);
	
	return Serializable;
}



