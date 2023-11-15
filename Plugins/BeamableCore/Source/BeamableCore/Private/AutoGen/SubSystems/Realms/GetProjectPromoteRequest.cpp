
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/GetProjectPromoteRequest.h"

void UGetProjectPromoteRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetProjectPromoteRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/realms/project/promote");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
	QueryParams.Appendf(TEXT("%s=%s"), TEXT("sourcePid"), *static_cast<FString>(SourcePid));
	bIsFirstQueryParam = false;
	
	if(Promotions.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		bIsFirstQueryParam = false;
	}

	if(ContentManifestIds.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		bIsFirstQueryParam = false;
	}

	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetProjectPromoteRequest::BuildBody(FString& BodyString) const
{
	
}

UGetProjectPromoteRequest* UGetProjectPromoteRequest::Make(FBeamPid _SourcePid, FOptionalArrayOfString _Promotions, FOptionalArrayOfString _ContentManifestIds, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetProjectPromoteRequest* Req = NewObject<UGetProjectPromoteRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->SourcePid = _SourcePid;
	Req->Promotions = _Promotions;
	Req->ContentManifestIds = _ContentManifestIds;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
