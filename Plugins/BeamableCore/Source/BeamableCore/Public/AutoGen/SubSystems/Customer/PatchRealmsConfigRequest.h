
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/RealmConfigChangeRequestBody.h"
#include "BeamableCore/Public/AutoGen/EmptyMessage.h"

#include "PatchRealmsConfigRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPatchRealmsConfigRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Customer Id", Category="Beam")
	FString CustomerId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Realm Id", Category="Beam")
	FString RealmId = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	URealmConfigChangeRequestBody* Body = {};

	// Beam Base Request Declaration
	UPatchRealmsConfigRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Customer|Utils|Make/Break", DisplayName="Make PatchRealmsConfig",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Deletes,_Upserts,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPatchRealmsConfigRequest* Make(FString _CustomerId, FString _RealmId, FOptionalArrayOfString _Deletes, FOptionalMapOfString _Upserts, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPatchRealmsConfigSuccess, FBeamRequestContext, Context, UPatchRealmsConfigRequest*, Request, UEmptyMessage*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPatchRealmsConfigError, FBeamRequestContext, Context, UPatchRealmsConfigRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPatchRealmsConfigComplete, FBeamRequestContext, Context, UPatchRealmsConfigRequest*, Request);

using FPatchRealmsConfigFullResponse = FBeamFullResponse<UPatchRealmsConfigRequest*, UEmptyMessage*>;
DECLARE_DELEGATE_OneParam(FOnPatchRealmsConfigFullResponse, FPatchRealmsConfigFullResponse);
