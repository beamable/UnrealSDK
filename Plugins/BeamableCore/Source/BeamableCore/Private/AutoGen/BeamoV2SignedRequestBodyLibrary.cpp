
#include "BeamableCore/Public/AutoGen/BeamoV2SignedRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeamoV2SignedRequestBodyLibrary::BeamoV2SignedRequestBodyToJsonString(const UBeamoV2SignedRequestBody* Serializable, const bool Pretty)
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

UBeamoV2SignedRequestBody* UBeamoV2SignedRequestBodyLibrary::Make(FOptionalString Url, FOptionalString Body, FOptionalString Method, FOptionalArrayOfBeamoV2StringStringKeyValuePair Headers, UObject* Outer)
{
	auto Serializable = NewObject<UBeamoV2SignedRequestBody>(Outer);
	Serializable->Url = Url;
	Serializable->Body = Body;
	Serializable->Method = Method;
	Serializable->Headers = Headers;
	
	return Serializable;
}

void UBeamoV2SignedRequestBodyLibrary::Break(const UBeamoV2SignedRequestBody* Serializable, FOptionalString& Url, FOptionalString& Body, FOptionalString& Method, FOptionalArrayOfBeamoV2StringStringKeyValuePair& Headers)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Url = Serializable->Url;
		Body = Serializable->Body;
		Method = Serializable->Method;
		Headers = Serializable->Headers;
	}
		
}

