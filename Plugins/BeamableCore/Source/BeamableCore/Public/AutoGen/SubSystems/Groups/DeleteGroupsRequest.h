
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/DisbandRequestBody.h"
#include "AutoGen/CommonResponse.h"

#include "DeleteGroupsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteGroupsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UDisbandRequestBody* Body;

	// Beam Base Request Declaration
	UDeleteGroupsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_SubGroup,Outer"))
	static UDeleteGroupsRequest* MakeDeleteGroupsRequest(int64 _ObjectId, FOptionalInt64 _SubGroup, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteGroupsSuccess, FBeamRequestContext, Context, UDeleteGroupsRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteGroupsError, FBeamRequestContext, Context, UDeleteGroupsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteGroupsComplete, FBeamRequestContext, Context, UDeleteGroupsRequest*, Request);

using FDeleteGroupsFullResponse = FBeamFullResponse<UDeleteGroupsRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnDeleteGroupsFullResponse, FDeleteGroupsFullResponse);
