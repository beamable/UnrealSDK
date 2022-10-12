
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/Optionals/OptionalInt64.h"
#include "AutoGen/Optionals/OptionalString.h"

#include "AutoGen/ListTokenResponse.h"

#include "GetTokenListRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetTokenListRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Page Size")
	int32 PageSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Page")
	int32 Page;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Cid")
	FOptionalInt64 Cid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Pid")
	FOptionalString Pid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Gamer Tag Or Account Id")
	int64 GamerTagOrAccountId;

	// Body Params
	

	// Beam Base Request Declaration
	UGetTokenListRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_Cid,_Pid,Outer"))
	static UGetTokenListRequest* MakeGetTokenListRequest(int32 _PageSize, int32 _Page, FOptionalInt64 _Cid, FOptionalString _Pid, int64 _GamerTagOrAccountId, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetTokenListSuccess, FBeamRequestContext, Context, UGetTokenListRequest*, Request, UListTokenResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetTokenListError, FBeamRequestContext, Context, UGetTokenListRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetTokenListComplete, FBeamRequestContext, Context, UGetTokenListRequest*, Request);

using FGetTokenListFullResponse = FBeamFullResponse<UGetTokenListRequest*, UListTokenResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetTokenListFullResponse, FGetTokenListFullResponse);
