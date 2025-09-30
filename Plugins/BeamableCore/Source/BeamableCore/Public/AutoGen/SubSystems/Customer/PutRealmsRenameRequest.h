
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/RenameRealmRequestBody.h"
#include "BeamableCore/Public/AutoGen/EmptyMessage.h"

#include "PutRealmsRenameRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutRealmsRenameRequest : public UObject, public IBeamBaseRequestInterface
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
	URenameRealmRequestBody* Body = {};

	// Beam Base Request Declaration
	UPutRealmsRenameRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Customer|Utils|Make/Break", DisplayName="Make PutRealmsRename",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPutRealmsRenameRequest* Make(FString _CustomerId, FString _RealmId, FString _NewName, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutRealmsRenameSuccess, FBeamRequestContext, Context, UPutRealmsRenameRequest*, Request, UEmptyMessage*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutRealmsRenameError, FBeamRequestContext, Context, UPutRealmsRenameRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutRealmsRenameComplete, FBeamRequestContext, Context, UPutRealmsRenameRequest*, Request);

using FPutRealmsRenameFullResponse = FBeamFullResponse<UPutRealmsRenameRequest*, UEmptyMessage*>;
DECLARE_DELEGATE_OneParam(FOnPutRealmsRenameFullResponse, FPutRealmsRenameFullResponse);
