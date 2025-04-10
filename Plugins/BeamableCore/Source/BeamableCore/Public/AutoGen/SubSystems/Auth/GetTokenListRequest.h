
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBeamCid.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBeamPid.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/ListTokenResponse.h"

#include "GetTokenListRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetTokenListRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Page Size", Category="Beam")
	int32 PageSize = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Page", Category="Beam")
	int32 Page = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Cid", Category="Beam")
	FOptionalBeamCid Cid = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Pid", Category="Beam")
	FOptionalBeamPid Pid = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Gamer Tag Or Account Id", Category="Beam")
	int64 GamerTagOrAccountId = {};

	// Body Params
	

	// Beam Base Request Declaration
	UGetTokenListRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Auth|Utils|Make/Break", DisplayName="Make GetTokenList",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Cid,_Pid,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetTokenListRequest* Make(int32 _PageSize, int32 _Page, FOptionalBeamCid _Cid, FOptionalBeamPid _Pid, int64 _GamerTagOrAccountId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetTokenListSuccess, FBeamRequestContext, Context, UGetTokenListRequest*, Request, UListTokenResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetTokenListError, FBeamRequestContext, Context, UGetTokenListRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetTokenListComplete, FBeamRequestContext, Context, UGetTokenListRequest*, Request);

using FGetTokenListFullResponse = FBeamFullResponse<UGetTokenListRequest*, UListTokenResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetTokenListFullResponse, FGetTokenListFullResponse);
