
#include "AutoGen/GetManifestRequestBodyLibrary.h"

#include "CoreMinimal.h"


FString UGetManifestRequestBodyLibrary::GetManifestRequestBodyToJsonString(const UGetManifestRequestBody* Serializable, const bool Pretty)
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

UGetManifestRequestBody* UGetManifestRequestBodyLibrary::Make(FString Id, FOptionalBool bArchived, UObject* Outer)
{
	auto Serializable = NewObject<UGetManifestRequestBody>(Outer);
	Serializable->Id = Id;
	Serializable->bArchived = bArchived;
	
	return Serializable;
}

void UGetManifestRequestBodyLibrary::Break(const UGetManifestRequestBody* Serializable, FString& Id, FOptionalBool& bArchived)
{
	Id = Serializable->Id;
	bArchived = Serializable->bArchived;
		
}

