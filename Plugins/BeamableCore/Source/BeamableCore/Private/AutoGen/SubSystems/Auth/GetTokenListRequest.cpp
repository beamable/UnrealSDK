
#include "BeamableCore/Public/AutoGen/SubSystems/Auth/GetTokenListRequest.h"

void UGetTokenListRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetTokenListRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/auth/token/list");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
	QueryParams.Appendf(TEXT("%s=%s"), TEXT("pageSize"), *FString::FromInt(PageSize));
	bIsFirstQueryParam = false;
	
	bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
	QueryParams.Appendf(TEXT("%s=%s"), TEXT("page"), *FString::FromInt(Page));
	bIsFirstQueryParam = false;
	
	if(Cid.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("cid"), *static_cast<FString>(Cid.Val));
		bIsFirstQueryParam = false;
	}

	if(Pid.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("pid"), *static_cast<FString>(Pid.Val));
		bIsFirstQueryParam = false;
	}

	bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
	QueryParams.Appendf(TEXT("%s=%s"), TEXT("gamerTagOrAccountId"), *FString::FromInt(GamerTagOrAccountId));
	bIsFirstQueryParam = false;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetTokenListRequest::BuildBody(FString& BodyString) const
{
	
}

UGetTokenListRequest* UGetTokenListRequest::Make(int32 _PageSize, int32 _Page, FOptionalBeamCid _Cid, FOptionalBeamPid _Pid, int64 _GamerTagOrAccountId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetTokenListRequest* Req = NewObject<UGetTokenListRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->PageSize = _PageSize;
	Req->Page = _Page;
	Req->Cid = _Cid;
	Req->Pid = _Pid;
	Req->GamerTagOrAccountId = _GamerTagOrAccountId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
