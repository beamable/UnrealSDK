
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/GetStatusForGroupsRequestBody.h"
#include "AutoGen/GetStatusForGroupsResponse.h"

#include "PostSearchGroupsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostSearchGroupsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UGetStatusForGroupsRequestBody* Body;

	// Beam Base Request Declaration
	UPostSearchGroupsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UPostSearchGroupsRequest* MakePostSearchGroupsRequest(TArray<int64> _GroupIds, FString _ContentId, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostSearchGroupsSuccess, FBeamRequestContext, Context, UPostSearchGroupsRequest*, Request, UGetStatusForGroupsResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostSearchGroupsError, FBeamRequestContext, Context, UPostSearchGroupsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostSearchGroupsComplete, FBeamRequestContext, Context, UPostSearchGroupsRequest*, Request);

using FPostSearchGroupsFullResponse = FBeamFullResponse<UPostSearchGroupsRequest*, UGetStatusForGroupsResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostSearchGroupsFullResponse, FPostSearchGroupsFullResponse);
