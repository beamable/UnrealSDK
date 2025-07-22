
#include "BeamableCore/Public/AutoGen/ListTokensRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UListTokensRequestBodyLibrary::ListTokensRequestBodyToJsonString(const UListTokensRequestBody* Serializable, const bool Pretty)
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

UListTokensRequestBody* UListTokensRequestBodyLibrary::Make(int32 PageSize, int32 Page, int64 GamerTagOrAccountId, FOptionalBeamCid Cid, FOptionalBeamPid Pid, UObject* Outer)
{
	auto Serializable = NewObject<UListTokensRequestBody>(Outer);
	Serializable->PageSize = PageSize;
	Serializable->Page = Page;
	Serializable->GamerTagOrAccountId = GamerTagOrAccountId;
	Serializable->Cid = Cid;
	Serializable->Pid = Pid;
	
	return Serializable;
}

void UListTokensRequestBodyLibrary::Break(const UListTokensRequestBody* Serializable, int32& PageSize, int32& Page, int64& GamerTagOrAccountId, FOptionalBeamCid& Cid, FOptionalBeamPid& Pid)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		PageSize = Serializable->PageSize;
		Page = Serializable->Page;
		GamerTagOrAccountId = Serializable->GamerTagOrAccountId;
		Cid = Serializable->Cid;
		Pid = Serializable->Pid;
	}
		
}

