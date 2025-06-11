
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/ObjectRequests.h"
#include "BeamableCore/Public/AutoGen/EmptyResponse.h"

#include "DeleteDataRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteDataRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UObjectRequests* Body = {};

	// Beam Base Request Declaration
	UDeleteDataRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Cloudsaving|Utils|Make/Break", DisplayName="Make DeleteData",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_PlayerId,_Request,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UDeleteDataRequest* Make(FOptionalInt64 _PlayerId, FOptionalArrayOfObjectRequestBody _Request, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteDataSuccess, FBeamRequestContext, Context, UDeleteDataRequest*, Request, UEmptyResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteDataError, FBeamRequestContext, Context, UDeleteDataRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteDataComplete, FBeamRequestContext, Context, UDeleteDataRequest*, Request);

using FDeleteDataFullResponse = FBeamFullResponse<UDeleteDataRequest*, UEmptyResponse*>;
DECLARE_DELEGATE_OneParam(FOnDeleteDataFullResponse, FDeleteDataFullResponse);
