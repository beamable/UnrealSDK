
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/PromoteRealmRequestBody.h"
#include "AutoGen/PromoteRealmResponseOld.h"

#include "PostProjectPromoteRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostProjectPromoteRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UPromoteRealmRequestBody* Body;

	// Beam Base Request Declaration
	UPostProjectPromoteRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_Promotions,_ContentManifestIds,Outer"))
	static UPostProjectPromoteRequest* MakePostProjectPromoteRequest(FString _SourcePid, FOptionalArrayOfString _Promotions, FOptionalArrayOfString _ContentManifestIds, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostProjectPromoteSuccess, FBeamRequestContext, Context, UPostProjectPromoteRequest*, Request, UPromoteRealmResponseOld*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostProjectPromoteError, FBeamRequestContext, Context, UPostProjectPromoteRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostProjectPromoteComplete, FBeamRequestContext, Context, UPostProjectPromoteRequest*, Request);

using FPostProjectPromoteFullResponse = FBeamFullResponse<UPostProjectPromoteRequest*, UPromoteRealmResponseOld*>;
DECLARE_DELEGATE_OneParam(FOnPostProjectPromoteFullResponse, FPostProjectPromoteFullResponse);
