
#include "BeamableCore/Public/AutoGen/SubSystems/Cloudsaving/PostDataReplaceRequest.h"

void UPostDataReplaceRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostDataReplaceRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/cloudsaving/data/replace");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostDataReplaceRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostDataReplaceRequest* UPostDataReplaceRequest::Make(int64 _SourcePlayerId, int64 _TargetPlayerId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostDataReplaceRequest* Req = NewObject<UPostDataReplaceRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UReplaceObjectsRequestBody>(Req);
	Req->Body->SourcePlayerId = _SourcePlayerId;
	Req->Body->TargetPlayerId = _TargetPlayerId;
	

	return Req;
}
