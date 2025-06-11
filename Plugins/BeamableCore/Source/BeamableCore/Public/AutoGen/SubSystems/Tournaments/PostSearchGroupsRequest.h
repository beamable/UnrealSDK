
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/GetStatusForGroupsRequestBody.h"
#include "BeamableCore/Public/AutoGen/GetStatusForGroupsResponse.h"

#include "PostSearchGroupsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostSearchGroupsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UGetStatusForGroupsRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostSearchGroupsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Tournaments|Utils|Make/Break", DisplayName="Make PostSearchGroups",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostSearchGroupsRequest* Make(FString _ContentId, TArray<int64> _GroupIds, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostSearchGroupsSuccess, FBeamRequestContext, Context, UPostSearchGroupsRequest*, Request, UGetStatusForGroupsResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostSearchGroupsError, FBeamRequestContext, Context, UPostSearchGroupsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostSearchGroupsComplete, FBeamRequestContext, Context, UPostSearchGroupsRequest*, Request);

using FPostSearchGroupsFullResponse = FBeamFullResponse<UPostSearchGroupsRequest*, UGetStatusForGroupsResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostSearchGroupsFullResponse, FPostSearchGroupsFullResponse);
