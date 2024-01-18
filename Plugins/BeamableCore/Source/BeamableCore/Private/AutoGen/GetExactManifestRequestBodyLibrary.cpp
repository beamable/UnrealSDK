
#include "BeamableCore/Public/AutoGen/GetExactManifestRequestBodyLibrary.h"

#include "CoreMinimal.h"


FString UGetExactManifestRequestBodyLibrary::GetExactManifestRequestBodyToJsonString(const UGetExactManifestRequestBody* Serializable, const bool Pretty)
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

UGetExactManifestRequestBody* UGetExactManifestRequestBodyLibrary::Make(FString Uid, UObject* Outer)
{
	auto Serializable = NewObject<UGetExactManifestRequestBody>(Outer);
	Serializable->Uid = Uid;
	
	return Serializable;
}

void UGetExactManifestRequestBodyLibrary::Break(const UGetExactManifestRequestBody* Serializable, FString& Uid)
{
	Uid = Serializable->Uid;
		
}

