
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/PutImageCommitRequest.h"

void UPutImageCommitRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UPutImageCommitRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/beamo/image/commit");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPutImageCommitRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPutImageCommitRequest* UPutImageCommitRequest::Make(UBeamoBasicReference* _Service, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPutImageCommitRequest* Req = NewObject<UPutImageCommitRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UCommitImageRequestBody>(Req);
	// Assumes the object is constructed and have the new request take ownership of the memory for it
	Req->Body->Service = _Service;
	Req->Body->Service->Rename(nullptr, Req);
	

	return Req;
}
