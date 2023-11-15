
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/GetUploadAPIRequest.h"

void UGetUploadAPIRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetUploadAPIRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/beamo/uploadAPI");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetUploadAPIRequest::BuildBody(FString& BodyString) const
{
	
}

UGetUploadAPIRequest* UGetUploadAPIRequest::Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetUploadAPIRequest* Req = NewObject<UGetUploadAPIRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
