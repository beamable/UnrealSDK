
#include "BeamableCore/Public/AutoGen/SubSystems/Content/GetManifestPublicRequest.h"

void UGetManifestPublicRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetManifestPublicRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/content/manifest/public");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	if(Id.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("id"), *static_cast<FString>(Id.Val));
		bIsFirstQueryParam = false;
	}

	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetManifestPublicRequest::BuildBody(FString& BodyString) const
{
	
}

UGetManifestPublicRequest* UGetManifestPublicRequest::Make(FOptionalBeamContentManifestId _Id, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetManifestPublicRequest* Req = NewObject<UGetManifestPublicRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->Id = _Id;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
