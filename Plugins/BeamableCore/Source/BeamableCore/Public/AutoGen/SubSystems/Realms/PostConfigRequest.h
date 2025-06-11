
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/RealmConfigChangeRequestBody.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#include "PostConfigRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostConfigRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	URealmConfigChangeRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostConfigRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make PostConfig",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Deletes,_Upserts,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostConfigRequest* Make(FOptionalArrayOfString _Deletes, FOptionalMapOfString _Upserts, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostConfigSuccess, FBeamRequestContext, Context, UPostConfigRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostConfigError, FBeamRequestContext, Context, UPostConfigRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostConfigComplete, FBeamRequestContext, Context, UPostConfigRequest*, Request);

using FPostConfigFullResponse = FBeamFullResponse<UPostConfigRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostConfigFullResponse, FPostConfigFullResponse);
