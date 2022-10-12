
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/GetSocialStatusesResponse.h"

#include "GetSocialRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetSocialRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Player Ids")
	TArray<FString> PlayerIds;

	// Body Params
	

	// Beam Base Request Declaration
	UGetSocialRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UGetSocialRequest* MakeGetSocialRequest(TArray<FString> _PlayerIds, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetSocialSuccess, FBeamRequestContext, Context, UGetSocialRequest*, Request, UGetSocialStatusesResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetSocialError, FBeamRequestContext, Context, UGetSocialRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetSocialComplete, FBeamRequestContext, Context, UGetSocialRequest*, Request);

using FGetSocialFullResponse = FBeamFullResponse<UGetSocialRequest*, UGetSocialStatusesResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetSocialFullResponse, FGetSocialFullResponse);
