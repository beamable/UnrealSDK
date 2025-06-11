
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamBackend/SemanticTypes/BeamPid.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfString.h"
#include "BeamableCore/Public/AutoGen/PromoteRealmResponse.h"

#include "GetPromotionRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetPromotionRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Source Pid", Category="Beam")
	FBeamPid SourcePid = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Promotions", Category="Beam")
	FOptionalArrayOfString Promotions = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Content Manifest Ids", Category="Beam")
	FOptionalArrayOfString ContentManifestIds = {};

	// Body Params
	

	// Beam Base Request Declaration
	UGetPromotionRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make GetPromotion",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Promotions,_ContentManifestIds,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetPromotionRequest* Make(FBeamPid _SourcePid, FOptionalArrayOfString _Promotions, FOptionalArrayOfString _ContentManifestIds, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetPromotionSuccess, FBeamRequestContext, Context, UGetPromotionRequest*, Request, UPromoteRealmResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetPromotionError, FBeamRequestContext, Context, UGetPromotionRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetPromotionComplete, FBeamRequestContext, Context, UGetPromotionRequest*, Request);

using FGetPromotionFullResponse = FBeamFullResponse<UGetPromotionRequest*, UPromoteRealmResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetPromotionFullResponse, FGetPromotionFullResponse);
