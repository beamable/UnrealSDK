
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/PromoteRealmRequestBody.h"
#include "BeamableCore/Public/AutoGen/PromoteRealmResponseOld.h"

#include "PostProjectPromoteRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostProjectPromoteRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UPromoteRealmRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostProjectPromoteRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make PostProjectPromote",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Promotions,_ContentManifestIds,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostProjectPromoteRequest* Make(FBeamPid _SourcePid, FOptionalArrayOfString _Promotions, FOptionalArrayOfString _ContentManifestIds, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostProjectPromoteSuccess, FBeamRequestContext, Context, UPostProjectPromoteRequest*, Request, UPromoteRealmResponseOld*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostProjectPromoteError, FBeamRequestContext, Context, UPostProjectPromoteRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostProjectPromoteComplete, FBeamRequestContext, Context, UPostProjectPromoteRequest*, Request);

using FPostProjectPromoteFullResponse = FBeamFullResponse<UPostProjectPromoteRequest*, UPromoteRealmResponseOld*>;
DECLARE_DELEGATE_OneParam(FOnPostProjectPromoteFullResponse, FPostProjectPromoteFullResponse);
