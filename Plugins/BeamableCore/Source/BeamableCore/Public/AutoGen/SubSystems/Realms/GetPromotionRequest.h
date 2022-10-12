
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/Optionals/OptionalArrayOfString.h"
#include "AutoGen/PromoteRealmResponse.h"

#include "GetPromotionRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetPromotionRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Source Pid")
	FString SourcePid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Promotions")
	FOptionalArrayOfString Promotions;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Content Manifest Ids")
	FOptionalArrayOfString ContentManifestIds;

	// Body Params
	

	// Beam Base Request Declaration
	UGetPromotionRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_Promotions,_ContentManifestIds,Outer"))
	static UGetPromotionRequest* MakeGetPromotionRequest(FString _SourcePid, FOptionalArrayOfString _Promotions, FOptionalArrayOfString _ContentManifestIds, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetPromotionSuccess, FBeamRequestContext, Context, UGetPromotionRequest*, Request, UPromoteRealmResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetPromotionError, FBeamRequestContext, Context, UGetPromotionRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetPromotionComplete, FBeamRequestContext, Context, UGetPromotionRequest*, Request);

using FGetPromotionFullResponse = FBeamFullResponse<UGetPromotionRequest*, UPromoteRealmResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetPromotionFullResponse, FGetPromotionFullResponse);
