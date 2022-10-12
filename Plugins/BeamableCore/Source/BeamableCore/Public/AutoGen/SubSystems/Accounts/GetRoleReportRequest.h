
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/AccountRolesReport.h"

#include "GetRoleReportRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetRoleReportRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UGetRoleReportRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UGetRoleReportRequest* MakeGetRoleReportRequest(int64 _ObjectId, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetRoleReportSuccess, FBeamRequestContext, Context, UGetRoleReportRequest*, Request, UAccountRolesReport*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetRoleReportError, FBeamRequestContext, Context, UGetRoleReportRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetRoleReportComplete, FBeamRequestContext, Context, UGetRoleReportRequest*, Request);

using FGetRoleReportFullResponse = FBeamFullResponse<UGetRoleReportRequest*, UAccountRolesReport*>;
DECLARE_DELEGATE_OneParam(FOnGetRoleReportFullResponse, FGetRoleReportFullResponse);
