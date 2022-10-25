
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"


#include "AutoGen/AccountRolesReport.h"

#include "GetRoleReportRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetRoleReportRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UGetRoleReportRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|Accounts", DisplayName="Beam - Make GetRoleReport",  meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UGetRoleReportRequest* Make(int64 _ObjectId, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetRoleReportSuccess, FBeamRequestContext, Context, UGetRoleReportRequest*, Request, UAccountRolesReport*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetRoleReportError, FBeamRequestContext, Context, UGetRoleReportRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetRoleReportComplete, FBeamRequestContext, Context, UGetRoleReportRequest*, Request);

using FGetRoleReportFullResponse = FBeamFullResponse<UGetRoleReportRequest*, UAccountRolesReport*>;
DECLARE_DELEGATE_OneParam(FOnGetRoleReportFullResponse, FGetRoleReportFullResponse);
