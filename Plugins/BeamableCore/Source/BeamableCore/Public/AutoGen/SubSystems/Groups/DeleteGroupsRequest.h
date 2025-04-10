
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/DisbandRequestBody.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#include "DeleteGroupsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteGroupsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	int64 ObjectId = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UDisbandRequestBody* Body = {};

	// Beam Base Request Declaration
	UDeleteGroupsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Groups|Utils|Make/Break", DisplayName="Make DeleteGroups",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_SubGroup,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UDeleteGroupsRequest* Make(int64 _ObjectId, FOptionalInt64 _SubGroup, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteGroupsSuccess, FBeamRequestContext, Context, UDeleteGroupsRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteGroupsError, FBeamRequestContext, Context, UDeleteGroupsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteGroupsComplete, FBeamRequestContext, Context, UDeleteGroupsRequest*, Request);

using FDeleteGroupsFullResponse = FBeamFullResponse<UDeleteGroupsRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnDeleteGroupsFullResponse, FDeleteGroupsFullResponse);
