
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/GetSampleStatRequestArgsLibrary.h"

#include "CoreMinimal.h"


FString UGetSampleStatRequestArgsLibrary::GetSampleStatRequestArgsToJsonString(const UGetSampleStatRequestArgs* Serializable, const bool Pretty)
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

UGetSampleStatRequestArgs* UGetSampleStatRequestArgsLibrary::Make(int64 GamerTag, UObject* Outer)
{
	auto Serializable = NewObject<UGetSampleStatRequestArgs>(Outer);
	Serializable->GamerTag = GamerTag;
	
	return Serializable;
}

void UGetSampleStatRequestArgsLibrary::Break(const UGetSampleStatRequestArgs* Serializable, int64& GamerTag)
{
	GamerTag = Serializable->GamerTag;
		
}

