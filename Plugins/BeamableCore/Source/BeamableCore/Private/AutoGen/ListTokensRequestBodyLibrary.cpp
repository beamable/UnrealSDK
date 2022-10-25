
#include "AutoGen/ListTokensRequestBodyLibrary.h"

#include "CoreMinimal.h"


FString UListTokensRequestBodyLibrary::ListTokensRequestBodyToJsonString(const UListTokensRequestBody* Serializable, const bool Pretty)
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

UListTokensRequestBody* UListTokensRequestBodyLibrary::Make(int32 PageSize, int32 Page, int64 GamerTagOrAccountId, FOptionalInt64 Cid, FOptionalString Pid, UObject* Outer)
{
	auto Serializable = NewObject<UListTokensRequestBody>(Outer);
	Serializable->PageSize = PageSize;
	Serializable->Page = Page;
	Serializable->GamerTagOrAccountId = GamerTagOrAccountId;
	Serializable->Cid = Cid;
	Serializable->Pid = Pid;
	
	return Serializable;
}

void UListTokensRequestBodyLibrary::Break(const UListTokensRequestBody* Serializable, int32& PageSize, int32& Page, int64& GamerTagOrAccountId, FOptionalInt64& Cid, FOptionalString& Pid)
{
	PageSize = Serializable->PageSize;
	Page = Serializable->Page;
	GamerTagOrAccountId = Serializable->GamerTagOrAccountId;
	Cid = Serializable->Cid;
	Pid = Serializable->Pid;
		
}

