
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/PromoteRealmRequestBody.h"
#include "BeamableCore/Public/AutoGen/PromoteRealmResponse.h"

#include "PostPromotionRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostPromotionRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UPromoteRealmRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostPromotionRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make PostPromotion",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Promotions,_ContentManifestIds,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostPromotionRequest* Make(FBeamPid _SourcePid, FOptionalArrayOfString _Promotions, FOptionalArrayOfString _ContentManifestIds, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostPromotionSuccess, FBeamRequestContext, Context, UPostPromotionRequest*, Request, UPromoteRealmResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostPromotionError, FBeamRequestContext, Context, UPostPromotionRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostPromotionComplete, FBeamRequestContext, Context, UPostPromotionRequest*, Request);

using FPostPromotionFullResponse = FBeamFullResponse<UPostPromotionRequest*, UPromoteRealmResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostPromotionFullResponse, FPostPromotionFullResponse);
