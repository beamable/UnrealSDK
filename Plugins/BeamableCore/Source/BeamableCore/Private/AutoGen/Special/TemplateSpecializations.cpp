#include "BeamBackend/BeamBackend.h"
#include "AutoGen/SubSystems/Content/GetManifestPublicRequest.h"
#include "AutoGen/SubSystems/Content/GetManifestChecksumRequest.h"
#include "AutoGen/SubSystems/Content/PostManifestsUnarchiveRequest.h"
#include "AutoGen/SubSystems/Content/BasicContentPostManifestPullRequest.h"
#include "AutoGen/SubSystems/Content/GetManifestHistoryRequest.h"
#include "AutoGen/SubSystems/Content/PostBinaryRequest.h"
#include "AutoGen/SubSystems/Content/PostManifestsPullRequest.h"
#include "AutoGen/SubSystems/Content/BasicContentGetContentRequest.h"
#include "AutoGen/SubSystems/Content/GetLocalizationsRequest.h"
#include "AutoGen/SubSystems/Content/PutLocalizationsRequest.h"
#include "AutoGen/SubSystems/Content/DeleteLocalizationsRequest.h"
#include "AutoGen/SubSystems/Content/PostTextRequest.h"
#include "AutoGen/SubSystems/Content/GetManifestExactRequest.h"
#include "AutoGen/SubSystems/Content/BasicContentGetManifestRequest.h"
#include "AutoGen/SubSystems/Content/BasicContentPostManifestRequest.h"
#include "AutoGen/SubSystems/Content/PostManifestsArchiveRequest.h"
#include "AutoGen/SubSystems/Content/PostContentRequest.h"
#include "AutoGen/SubSystems/Content/PutManifestRepeatRequest.h"
#include "AutoGen/SubSystems/Content/GetManifestPrivateRequest.h"
#include "AutoGen/SubSystems/Content/GetManifestChecksumsRequest.h"
#include "AutoGen/SubSystems/Content/BasicContentGetManifestsRequest.h"
#include "AutoGen/SubSystems/Beamo/PostMetricsUrlRequest.h"
#include "AutoGen/SubSystems/Beamo/GetStoragePerformanceRequest.h"
#include "AutoGen/SubSystems/Beamo/BasicBeamoGetManifestsRequest.h"
#include "AutoGen/SubSystems/Beamo/GetTemplatesRequest.h"
#include "AutoGen/SubSystems/Beamo/PostLogsUrlRequest.h"
#include "AutoGen/SubSystems/Beamo/GetUploadAPIRequest.h"
#include "AutoGen/SubSystems/Beamo/GetStatusRequest.h"
#include "AutoGen/SubSystems/Beamo/GetManifestCurrentRequest.h"
#include "AutoGen/SubSystems/Beamo/BasicBeamoPostManifestPullRequest.h"
#include "AutoGen/SubSystems/Beamo/GetRegistryRequest.h"
#include "AutoGen/SubSystems/Beamo/PostManifestDeployRequest.h"
#include "AutoGen/SubSystems/Beamo/GetStorageConnectionRequest.h"
#include "AutoGen/SubSystems/Beamo/BasicBeamoGetManifestRequest.h"
#include "AutoGen/SubSystems/Beamo/BasicBeamoPostManifestRequest.h"
#include "AutoGen/SubSystems/EventPlayers/GetEventPlayersRequest.h"
#include "AutoGen/SubSystems/EventPlayers/ObjectEventPlayersPostClaimRequest.h"
#include "AutoGen/SubSystems/EventPlayers/PutScoreRequest.h"
#include "AutoGen/SubSystems/Events/GetRunningRequest.h"
#include "AutoGen/SubSystems/Events/BasicEventsGetContentRequest.h"
#include "AutoGen/SubSystems/Events/GetCalendarRequest.h"
#include "AutoGen/SubSystems/Events/PostApplyContentRequest.h"
#include "AutoGen/SubSystems/Events/PutEndPhaseRequest.h"
#include "AutoGen/SubSystems/Events/GetEventsRequest.h"
#include "AutoGen/SubSystems/Events/GetPingRequest.h"
#include "AutoGen/SubSystems/Events/PutContentRequest.h"
#include "AutoGen/SubSystems/Events/DeleteContentRequest.h"
#include "AutoGen/SubSystems/Events/PutRefreshRequest.h"
#include "AutoGen/SubSystems/GroupUsers/GetAvailabilityRequest.h"
#include "AutoGen/SubSystems/GroupUsers/GetRecommendedRequest.h"
#include "AutoGen/SubSystems/GroupUsers/PostJoinRequest.h"
#include "AutoGen/SubSystems/GroupUsers/DeleteJoinRequest.h"
#include "AutoGen/SubSystems/GroupUsers/PostGroupRequest.h"
#include "AutoGen/SubSystems/GroupUsers/ObjectGroupUsersGetSearchRequest.h"
#include "AutoGen/SubSystems/GroupUsers/GetGroupUsersRequest.h"
#include "AutoGen/SubSystems/Groups/PostKickRequest.h"
#include "AutoGen/SubSystems/Groups/DeleteMemberRequest.h"
#include "AutoGen/SubSystems/Groups/ObjectGroupsGetGroupsRequest.h"
#include "AutoGen/SubSystems/Groups/PutGroupsRequest.h"
#include "AutoGen/SubSystems/Groups/DeleteGroupsRequest.h"
#include "AutoGen/SubSystems/Groups/ObjectGroupsPutRoleRequest.h"
#include "AutoGen/SubSystems/Groups/PostApplyRequest.h"
#include "AutoGen/SubSystems/Groups/PostDonationsRequest.h"
#include "AutoGen/SubSystems/Groups/PutDonationsRequest.h"
#include "AutoGen/SubSystems/Groups/PutDonationsClaimRequest.h"
#include "AutoGen/SubSystems/Groups/PostInviteRequest.h"
#include "AutoGen/SubSystems/Groups/PostPetitionRequest.h"
#include "AutoGen/SubSystems/Inventory/GetItemsRequest.h"
#include "AutoGen/SubSystems/Inventory/GetCurrencyRequest.h"
#include "AutoGen/SubSystems/Inventory/PutPreviewRequest.h"
#include "AutoGen/SubSystems/Inventory/GetMultipliersRequest.h"
#include "AutoGen/SubSystems/Inventory/GetInventoryRequest.h"
#include "AutoGen/SubSystems/Inventory/PostInventoryRequest.h"
#include "AutoGen/SubSystems/Inventory/PutInventoryRequest.h"
#include "AutoGen/SubSystems/Inventory/DeleteTransactionRequest.h"
#include "AutoGen/SubSystems/Inventory/PutTransferRequest.h"
#include "AutoGen/SubSystems/Leaderboards/GetRanksRequest.h"
#include "AutoGen/SubSystems/Leaderboards/GetMatchesRequest.h"
#include "AutoGen/SubSystems/Leaderboards/PutEntryRequest.h"
#include "AutoGen/SubSystems/Leaderboards/GetViewRequest.h"
#include "AutoGen/SubSystems/Leaderboards/BasicLeaderboardsGetListRequest.h"
#include "AutoGen/SubSystems/Leaderboards/GetPlayerRequest.h"
#include "AutoGen/SubSystems/Leaderboards/BasicLeaderboardsGetAssignmentRequest.h"
#include "AutoGen/SubSystems/Leaderboards/GetUidRequest.h"
#include "AutoGen/SubSystems/Leaderboards/DeleteEntriesRequest.h"
#include "AutoGen/SubSystems/Leaderboards/GetMembershipRequest.h"
#include "AutoGen/SubSystems/Leaderboards/GetPartitionRequest.h"
#include "AutoGen/SubSystems/Leaderboards/GetFriendsRequest.h"
#include "AutoGen/SubSystems/Leaderboards/PostLeaderboardsRequest.h"
#include "AutoGen/SubSystems/Leaderboards/DeleteLeaderboardsRequest.h"
#include "AutoGen/SubSystems/Leaderboards/ObjectLeaderboardsGetAssignmentRequest.h"
#include "AutoGen/SubSystems/Leaderboards/DeleteAssignmentRequest.h"
#include "AutoGen/SubSystems/Leaderboards/DeleteEntryRequest.h"
#include "AutoGen/SubSystems/Leaderboards/PutFreezeRequest.h"
#include "AutoGen/SubSystems/Leaderboards/GetDetailsRequest.h"
#include "AutoGen/SubSystems/Leaderboards/PutSwapRequest.h"
#include "AutoGen/SubSystems/Accounts/GetGetPersonallyIdentifiableInformationRequest.h"
#include "AutoGen/SubSystems/Accounts/GetAvailableThirdPartyRequest.h"
#include "AutoGen/SubSystems/Accounts/PostPasswordUpdateInitRequest.h"
#include "AutoGen/SubSystems/Accounts/GetAvailableDeviceIdRequest.h"
#include "AutoGen/SubSystems/Accounts/GetAvailableRequest.h"
#include "AutoGen/SubSystems/Accounts/PostPasswordUpdateConfirmRequest.h"
#include "AutoGen/SubSystems/Accounts/GetAvailableRolesRequest.h"
#include "AutoGen/SubSystems/Accounts/DeleteMeDeviceRequest.h"
#include "AutoGen/SubSystems/Accounts/BasicAccountsGetMeRequest.h"
#include "AutoGen/SubSystems/Accounts/PutMeRequest.h"
#include "AutoGen/SubSystems/Accounts/DeleteMeThirdPartyRequest.h"
#include "AutoGen/SubSystems/Accounts/BasicAccountsGetSearchRequest.h"
#include "AutoGen/SubSystems/Accounts/PostEmailUpdateInitRequest.h"
#include "AutoGen/SubSystems/Accounts/PostEmailUpdateConfirmRequest.h"
#include "AutoGen/SubSystems/Accounts/PostAdminAdminUserRequest.h"
#include "AutoGen/SubSystems/Accounts/BasicAccountsPostRegisterRequest.h"
#include "AutoGen/SubSystems/Accounts/GetAdminMeRequest.h"
#include "AutoGen/SubSystems/Accounts/GetAdminAdminUsersRequest.h"
#include "AutoGen/SubSystems/Accounts/GetFindRequest.h"
#include "AutoGen/SubSystems/Accounts/PostExternal_identityRequest.h"
#include "AutoGen/SubSystems/Accounts/DeleteExternal_identityRequest.h"
#include "AutoGen/SubSystems/Accounts/PutAdminEmailRequest.h"
#include "AutoGen/SubSystems/Accounts/GetRoleReportRequest.h"
#include "AutoGen/SubSystems/Accounts/ObjectAccountsPutRoleRequest.h"
#include "AutoGen/SubSystems/Accounts/DeleteRoleRequest.h"
#include "AutoGen/SubSystems/Accounts/PutAdminScopeRequest.h"
#include "AutoGen/SubSystems/Accounts/DeleteAdminScopeRequest.h"
#include "AutoGen/SubSystems/Accounts/PutAdminThirdPartyRequest.h"
#include "AutoGen/SubSystems/Accounts/DeleteAdminThirdPartyRequest.h"
#include "AutoGen/SubSystems/Accounts/PutAccountsRequest.h"
#include "AutoGen/SubSystems/Accounts/DeleteAdminForgetRequest.h"
#include "AutoGen/SubSystems/Stats/GetClientBatchRequest.h"
#include "AutoGen/SubSystems/Stats/PostClientStringlistRequest.h"
#include "AutoGen/SubSystems/Stats/GetClientRequest.h"
#include "AutoGen/SubSystems/Stats/PostClientRequest.h"
#include "AutoGen/SubSystems/Stats/PutSubscribeRequest.h"
#include "AutoGen/SubSystems/Stats/PostBatchRequest.h"
#include "AutoGen/SubSystems/Stats/BasicStatsPostSearchRequest.h"
#include "AutoGen/SubSystems/Stats/PostSearchExtendedRequest.h"
#include "AutoGen/SubSystems/Stats/GetStatsRequest.h"
#include "AutoGen/SubSystems/Stats/PostStatsRequest.h"
#include "AutoGen/SubSystems/Stats/DeleteStatsRequest.h"
#include "AutoGen/SubSystems/Tournaments/PostSearchGroupsRequest.h"
#include "AutoGen/SubSystems/Tournaments/BasicTournamentsGetTournamentsRequest.h"
#include "AutoGen/SubSystems/Tournaments/PostScoreRequest.h"
#include "AutoGen/SubSystems/Tournaments/ObjectTournamentsGetTournamentsRequest.h"
#include "AutoGen/SubSystems/Tournaments/PostTournamentsRequest.h"
#include "AutoGen/SubSystems/Tournaments/GetMeGroupRequest.h"
#include "AutoGen/SubSystems/Tournaments/GetRewardsRequest.h"
#include "AutoGen/SubSystems/Tournaments/PostRewardsRequest.h"
#include "AutoGen/SubSystems/Tournaments/GetGlobalRequest.h"
#include "AutoGen/SubSystems/Tournaments/GetStandingsGroupRequest.h"
#include "AutoGen/SubSystems/Tournaments/GetStandingsRequest.h"
#include "AutoGen/SubSystems/Tournaments/GetAdminPlayerRequest.h"
#include "AutoGen/SubSystems/Tournaments/PutAdminPlayerRequest.h"
#include "AutoGen/SubSystems/Tournaments/BasicTournamentsGetMeRequest.h"
#include "AutoGen/SubSystems/Tournaments/GetChampionsRequest.h"
#include "AutoGen/SubSystems/Tournaments/BasicTournamentsGetGroupsRequest.h"
#include "AutoGen/SubSystems/Auth/GetTokenRequest.h"
#include "AutoGen/SubSystems/Auth/AuthenticateRequest.h"
#include "AutoGen/SubSystems/Auth/GetTokenListRequest.h"
#include "AutoGen/SubSystems/Auth/PutTokenRevokeRequest.h"
#include "AutoGen/SubSystems/Cloudsaving/GetCloudsavingRequest.h"
#include "AutoGen/SubSystems/Cloudsaving/PostDataReplaceRequest.h"
#include "AutoGen/SubSystems/Cloudsaving/DeleteDataRequest.h"
#include "AutoGen/SubSystems/Cloudsaving/PostDataDownloadURLRequest.h"
#include "AutoGen/SubSystems/Cloudsaving/GetDataMetadataRequest.h"
#include "AutoGen/SubSystems/Cloudsaving/PostDataDownloadURLFromPortalRequest.h"
#include "AutoGen/SubSystems/Cloudsaving/PutDataMoveRequest.h"
#include "AutoGen/SubSystems/Cloudsaving/PutDataMoveFromPortalRequest.h"
#include "AutoGen/SubSystems/Cloudsaving/PostDataUploadURLFromPortalRequest.h"
#include "AutoGen/SubSystems/Cloudsaving/PutDataCommitManifestRequest.h"
#include "AutoGen/SubSystems/Cloudsaving/PostDataUploadURLRequest.h"
#include "AutoGen/SubSystems/Payments/PostWindowsPurchaseTrackRequest.h"
#include "AutoGen/SubSystems/Payments/GetAuditsRequest.h"
#include "AutoGen/SubSystems/Payments/PostWindowsPurchaseCompleteRequest.h"
#include "AutoGen/SubSystems/Payments/GetFacebookUpdateRequest.h"
#include "AutoGen/SubSystems/Payments/PostFacebookUpdateRequest.h"
#include "AutoGen/SubSystems/Payments/PostFacebookPurchaseCompleteRequest.h"
#include "AutoGen/SubSystems/Payments/PostTestPurchaseCompleteRequest.h"
#include "AutoGen/SubSystems/Payments/GetItunesProductRequest.h"
#include "AutoGen/SubSystems/Payments/PostGoogleplayPurchaseCompleteRequest.h"
#include "AutoGen/SubSystems/Payments/PostTestPurchaseTrackRequest.h"
#include "AutoGen/SubSystems/Payments/PostGoogleplayPurchaseVerifyRequest.h"
#include "AutoGen/SubSystems/Payments/PostCouponPurchaseTrackRequest.h"
#include "AutoGen/SubSystems/Payments/PostSteamPurchaseCompleteRequest.h"
#include "AutoGen/SubSystems/Payments/PostFacebookPurchaseTrackRequest.h"
#include "AutoGen/SubSystems/Payments/PostTestPurchaseVerifyRequest.h"
#include "AutoGen/SubSystems/Payments/PostGoogleplayPurchaseTrackRequest.h"
#include "AutoGen/SubSystems/Payments/GetSteamPricesRequest.h"
#include "AutoGen/SubSystems/Payments/PostWindowsPurchaseVerifyRequest.h"
#include "AutoGen/SubSystems/Payments/PostItunesPurchaseVerifyRequest.h"
#include "AutoGen/SubSystems/Payments/PostItunesPurchaseCompleteRequest.h"
#include "AutoGen/SubSystems/Payments/PostFacebookPurchaseVerifyRequest.h"
#include "AutoGen/SubSystems/Payments/PostSteamPurchaseTrackRequest.h"
#include "AutoGen/SubSystems/Payments/PostCouponPurchaseVerifyRequest.h"
#include "AutoGen/SubSystems/Payments/GetWindowsProductRequest.h"
#include "AutoGen/SubSystems/Payments/GetFacebookProductRequest.h"
#include "AutoGen/SubSystems/Payments/GetCouponProductRequest.h"
#include "AutoGen/SubSystems/Payments/GetSteamProductsRequest.h"
#include "AutoGen/SubSystems/Payments/PostSteamAuthRequest.h"
#include "AutoGen/SubSystems/Payments/GetSteamProductRequest.h"
#include "AutoGen/SubSystems/Payments/PostCouponPurchaseCompleteRequest.h"
#include "AutoGen/SubSystems/Payments/GetGoogleplayProductRequest.h"
#include "AutoGen/SubSystems/Payments/GetTestProductRequest.h"
#include "AutoGen/SubSystems/Payments/PostSteamPurchaseVerifyRequest.h"
#include "AutoGen/SubSystems/Payments/PostItunesPurchaseTrackRequest.h"
#include "AutoGen/SubSystems/Payments/GetPaymentsRequest.h"
#include "AutoGen/SubSystems/Payments/PostTestPurchaseBeginRequest.h"
#include "AutoGen/SubSystems/Payments/PostSteamPurchaseFailRequest.h"
#include "AutoGen/SubSystems/Payments/PostFacebookPurchaseFailRequest.h"
#include "AutoGen/SubSystems/Payments/PostGoogleplayPurchaseBeginRequest.h"
#include "AutoGen/SubSystems/Payments/PostItunesPurchaseBeginRequest.h"
#include "AutoGen/SubSystems/Payments/PostFacebookPurchaseCancelRequest.h"
#include "AutoGen/SubSystems/Payments/PostItunesPurchaseFailRequest.h"
#include "AutoGen/SubSystems/Payments/PostTestPurchaseCancelRequest.h"
#include "AutoGen/SubSystems/Payments/PostTestPurchaseFailRequest.h"
#include "AutoGen/SubSystems/Payments/PostCouponPurchaseCancelRequest.h"
#include "AutoGen/SubSystems/Payments/PostCouponPurchaseBeginRequest.h"
#include "AutoGen/SubSystems/Payments/PostFacebookPurchaseBeginRequest.h"
#include "AutoGen/SubSystems/Payments/GetSteamOrderRequest.h"
#include "AutoGen/SubSystems/Payments/PostWindowsPurchaseBeginRequest.h"
#include "AutoGen/SubSystems/Payments/PostGoogleplayPurchaseFailRequest.h"
#include "AutoGen/SubSystems/Payments/PostGoogleplayPurchaseCancelRequest.h"
#include "AutoGen/SubSystems/Payments/PostCouponPurchaseFailRequest.h"
#include "AutoGen/SubSystems/Payments/PostSteamPurchaseBeginRequest.h"
#include "AutoGen/SubSystems/Payments/PostSteamPurchaseCancelRequest.h"
#include "AutoGen/SubSystems/Payments/PostWindowsPurchaseCancelRequest.h"
#include "AutoGen/SubSystems/Payments/PostWindowsPurchaseFailRequest.h"
#include "AutoGen/SubSystems/Payments/PostItunesPurchaseCancelRequest.h"
#include "AutoGen/SubSystems/Push/BasicPushPostRegisterRequest.h"
#include "AutoGen/SubSystems/Push/PostSendRequest.h"
#include "AutoGen/SubSystems/Notification/PostPlayerRequest.h"
#include "AutoGen/SubSystems/Notification/PostCustomRequest.h"
#include "AutoGen/SubSystems/Notification/PostServerRequest.h"
#include "AutoGen/SubSystems/Notification/PostGenericRequest.h"
#include "AutoGen/SubSystems/Notification/GetNotificationRequest.h"
#include "AutoGen/SubSystems/Notification/BasicNotificationPostGameRequest.h"
#include "AutoGen/SubSystems/Realms/GetCustomerAliasAvailableRequest.h"
#include "AutoGen/SubSystems/Realms/GetProjectRequest.h"
#include "AutoGen/SubSystems/Realms/GetClientDefaultsRequest.h"
#include "AutoGen/SubSystems/Realms/PostCustomerRequest.h"
#include "AutoGen/SubSystems/Realms/GetIsCustomerRequest.h"
#include "AutoGen/SubSystems/Realms/GetCustomersRequest.h"
#include "AutoGen/SubSystems/Realms/PostProjectBeamableRequest.h"
#include "AutoGen/SubSystems/Realms/PostProjectRequest.h"
#include "AutoGen/SubSystems/Realms/PutProjectRequest.h"
#include "AutoGen/SubSystems/Realms/DeleteProjectRequest.h"
#include "AutoGen/SubSystems/Realms/GetGamesRequest.h"
#include "AutoGen/SubSystems/Realms/GetConfigRequest.h"
#include "AutoGen/SubSystems/Realms/PutConfigRequest.h"
#include "AutoGen/SubSystems/Realms/PutProjectRenameRequest.h"
#include "AutoGen/SubSystems/Realms/GetPlansRequest.h"
#include "AutoGen/SubSystems/Realms/PostPlansRequest.h"
#include "AutoGen/SubSystems/Realms/GetCustomerRequest.h"
#include "AutoGen/SubSystems/Realms/GetLaunchMessageRequest.h"
#include "AutoGen/SubSystems/Realms/PostLaunchMessageRequest.h"
#include "AutoGen/SubSystems/Realms/DeleteLaunchMessageRequest.h"
#include "AutoGen/SubSystems/Realms/GetAdminCustomerRequest.h"
#include "AutoGen/SubSystems/Realms/GetGameRequest.h"
#include "AutoGen/SubSystems/Realms/BasicRealmsPostGameRequest.h"
#include "AutoGen/SubSystems/Realms/PutGameRequest.h"
#include "AutoGen/SubSystems/Realms/GetProjectPromoteRequest.h"
#include "AutoGen/SubSystems/Realms/PostProjectPromoteRequest.h"
#include "AutoGen/SubSystems/Realms/GetPromotionRequest.h"
#include "AutoGen/SubSystems/Realms/PostPromotionRequest.h"
#include "AutoGen/SubSystems/Social/GetMyRequest.h"
#include "AutoGen/SubSystems/Social/PostFriendsInviteRequest.h"
#include "AutoGen/SubSystems/Social/DeleteFriendsInviteRequest.h"
#include "AutoGen/SubSystems/Social/DeleteFriendsRequest.h"
#include "AutoGen/SubSystems/Social/PostFriendsImportRequest.h"
#include "AutoGen/SubSystems/Social/PostFriendsMakeRequest.h"
#include "AutoGen/SubSystems/Social/GetSocialRequest.h"
#include "AutoGen/SubSystems/Social/PostBlockedRequest.h"
#include "AutoGen/SubSystems/Social/DeleteBlockedRequest.h"
#include "AutoGen/SubSystems/ChatV2/GetRoomsRequest.h"
#include "AutoGen/SubSystems/ChatV2/PostRoomsRequest.h"
#include "AutoGen/SubSystems/ChatV2/DeleteRoomsRequest.h"
#include "AutoGen/SubSystems/ChatV2/GetChatV2Request.h"
#include "AutoGen/SubSystems/ChatV2/PostMessagesRequest.h"
#include "AutoGen/SubSystems/Matchmaking/PutTickRequest.h"
#include "AutoGen/SubSystems/Matchmaking/GetMatchRequest.h"
#include "AutoGen/SubSystems/Matchmaking/PostMatchRequest.h"
#include "AutoGen/SubSystems/Matchmaking/DeleteMatchRequest.h"
#include "AutoGen/SubSystems/Commerce/GetSkusRequest.h"
#include "AutoGen/SubSystems/Commerce/GetCouponsCountRequest.h"
#include "AutoGen/SubSystems/Commerce/PostCatalogLegacyRequest.h"
#include "AutoGen/SubSystems/Commerce/GetCatalogRequest.h"
#include "AutoGen/SubSystems/Commerce/PostSkusRequest.h"
#include "AutoGen/SubSystems/Commerce/GetCommerceRequest.h"
#include "AutoGen/SubSystems/Commerce/PutListingsCooldownRequest.h"
#include "AutoGen/SubSystems/Commerce/GetOffersAdminRequest.h"
#include "AutoGen/SubSystems/Commerce/PostPurchaseRequest.h"
#include "AutoGen/SubSystems/Commerce/PutPurchaseRequest.h"
#include "AutoGen/SubSystems/Commerce/GetListingsRequest.h"
#include "AutoGen/SubSystems/Commerce/DeleteStatusRequest.h"
#include "AutoGen/SubSystems/Commerce/PostCouponsRequest.h"
#include "AutoGen/SubSystems/Commerce/PostStatsUpdateRequest.h"
#include "AutoGen/SubSystems/Commerce/GetOffersRequest.h"
#include "AutoGen/SubSystems/Calendars/ObjectCalendarsPostClaimRequest.h"
#include "AutoGen/SubSystems/Calendars/GetCalendarsRequest.h"
#include "AutoGen/SubSystems/Announcements/GetListTagsRequest.h"
#include "AutoGen/SubSystems/Announcements/BasicAnnouncementsGetListRequest.h"
#include "AutoGen/SubSystems/Announcements/BasicAnnouncementsGetSearchRequest.h"
#include "AutoGen/SubSystems/Announcements/GetListDefinitionsRequest.h"
#include "AutoGen/SubSystems/Announcements/PostAnnouncementsRequest.h"
#include "AutoGen/SubSystems/Announcements/BasicAnnouncementsDeleteAnnouncementsRequest.h"
#include "AutoGen/SubSystems/Announcements/BasicAnnouncementsGetContentRequest.h"
#include "AutoGen/SubSystems/Announcements/PutReadRequest.h"
#include "AutoGen/SubSystems/Announcements/ObjectAnnouncementsPostClaimRequest.h"
#include "AutoGen/SubSystems/Announcements/GetRawRequest.h"
#include "AutoGen/SubSystems/Announcements/GetAnnouncementsRequest.h"
#include "AutoGen/SubSystems/Announcements/ObjectAnnouncementsDeleteAnnouncementsRequest.h"
#include "AutoGen/SubSystems/Mail/GetTemplateRequest.h"
#include "AutoGen/SubSystems/Mail/BasicMailGetMailRequest.h"
#include "AutoGen/SubSystems/Mail/GetDetailRequest.h"
#include "AutoGen/SubSystems/Mail/GetCategoriesRequest.h"
#include "AutoGen/SubSystems/Mail/ObjectMailPostSearchRequest.h"
#include "AutoGen/SubSystems/Mail/PutBulkRequest.h"
#include "AutoGen/SubSystems/Mail/PutAcceptManyRequest.h"
#include "AutoGen/SubSystems/Mail/ObjectMailGetMailRequest.h"
#include "AutoGen/SubSystems/Mail/ObjectMailPutMailRequest.h"
#include "AutoGen/SubSystems/Mail/PutAttachmentsRequest.h"
#include "AutoGen/SubSystems/Mail/BasicMailPutMailRequest.h"
#include "AutoGen/SubSystems/Mail/BasicMailPostBulkRequest.h"
#include "AutoGen/SubSystems/Mail/ObjectMailPostBulkRequest.h"
#include "AutoGen/SubSystems/Mail/PostMailRequest.h"

template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetManifestPublicRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetManifestPublicRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetManifestPublicRequest, UClientManifestCsvResponse>(
	const int64&, UGetManifestPublicRequest*, FOnGetManifestPublicSuccess, FOnGetManifestPublicError, FOnGetManifestPublicComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetManifestPublicRequest, UClientManifestCsvResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetManifestPublicRequest*, FOnGetManifestPublicSuccess, FOnGetManifestPublicError, FOnGetManifestPublicComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetManifestPublicRequest*, TBeamFullResponseHandler<UGetManifestPublicRequest*, UClientManifestCsvResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetManifestPublicRequest*,
                                                                                   TBeamFullResponseHandler<UGetManifestPublicRequest*, UClientManifestCsvResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetManifestChecksumRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetManifestChecksumRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetManifestChecksumRequest, UContentBasicManifestChecksum>(
	const int64&, UGetManifestChecksumRequest*, FOnGetManifestChecksumSuccess, FOnGetManifestChecksumError, FOnGetManifestChecksumComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetManifestChecksumRequest, UContentBasicManifestChecksum>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetManifestChecksumRequest*, FOnGetManifestChecksumSuccess, FOnGetManifestChecksumError, FOnGetManifestChecksumComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetManifestChecksumRequest*, TBeamFullResponseHandler<UGetManifestChecksumRequest*, UContentBasicManifestChecksum*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetManifestChecksumRequest*,
                                                                                   TBeamFullResponseHandler<UGetManifestChecksumRequest*, UContentBasicManifestChecksum*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostManifestsUnarchiveRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostManifestsUnarchiveRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostManifestsUnarchiveRequest, UEmptyResponse>(
	const int64&, UPostManifestsUnarchiveRequest*, FOnPostManifestsUnarchiveSuccess, FOnPostManifestsUnarchiveError, FOnPostManifestsUnarchiveComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostManifestsUnarchiveRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostManifestsUnarchiveRequest*, FOnPostManifestsUnarchiveSuccess, FOnPostManifestsUnarchiveError, FOnPostManifestsUnarchiveComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostManifestsUnarchiveRequest*, TBeamFullResponseHandler<UPostManifestsUnarchiveRequest*, UEmptyResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostManifestsUnarchiveRequest*,
                                                                                   TBeamFullResponseHandler<UPostManifestsUnarchiveRequest*, UEmptyResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UBasicContentPostManifestPullRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UBasicContentPostManifestPullRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UBasicContentPostManifestPullRequest, UContentBasicManifest>(
	const int64&, UBasicContentPostManifestPullRequest*, FOnBasicContentPostManifestPullSuccess, FOnBasicContentPostManifestPullError, FOnBasicContentPostManifestPullComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UBasicContentPostManifestPullRequest, UContentBasicManifest>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicContentPostManifestPullRequest*, FOnBasicContentPostManifestPullSuccess, FOnBasicContentPostManifestPullError, FOnBasicContentPostManifestPullComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UBasicContentPostManifestPullRequest*, TBeamFullResponseHandler<UBasicContentPostManifestPullRequest*, UContentBasicManifest*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicContentPostManifestPullRequest*,
                                                                                   TBeamFullResponseHandler<UBasicContentPostManifestPullRequest*, UContentBasicManifest*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetManifestHistoryRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetManifestHistoryRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetManifestHistoryRequest, UGetManifestHistoryResponse>(
	const int64&, UGetManifestHistoryRequest*, FOnGetManifestHistorySuccess, FOnGetManifestHistoryError, FOnGetManifestHistoryComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetManifestHistoryRequest, UGetManifestHistoryResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetManifestHistoryRequest*, FOnGetManifestHistorySuccess, FOnGetManifestHistoryError, FOnGetManifestHistoryComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetManifestHistoryRequest*, TBeamFullResponseHandler<UGetManifestHistoryRequest*, UGetManifestHistoryResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetManifestHistoryRequest*,
                                                                                   TBeamFullResponseHandler<UGetManifestHistoryRequest*, UGetManifestHistoryResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostBinaryRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostBinaryRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostBinaryRequest, USaveBinaryResponse>(
	const int64&, UPostBinaryRequest*, FOnPostBinarySuccess, FOnPostBinaryError, FOnPostBinaryComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostBinaryRequest, USaveBinaryResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostBinaryRequest*, FOnPostBinarySuccess, FOnPostBinaryError, FOnPostBinaryComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostBinaryRequest*, TBeamFullResponseHandler<UPostBinaryRequest*, USaveBinaryResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostBinaryRequest*,
                                                                                   TBeamFullResponseHandler<UPostBinaryRequest*, USaveBinaryResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostManifestsPullRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostManifestsPullRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostManifestsPullRequest, UManifestChecksums>(
	const int64&, UPostManifestsPullRequest*, FOnPostManifestsPullSuccess, FOnPostManifestsPullError, FOnPostManifestsPullComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostManifestsPullRequest, UManifestChecksums>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostManifestsPullRequest*, FOnPostManifestsPullSuccess, FOnPostManifestsPullError, FOnPostManifestsPullComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostManifestsPullRequest*, TBeamFullResponseHandler<UPostManifestsPullRequest*, UManifestChecksums*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostManifestsPullRequest*,
                                                                                   TBeamFullResponseHandler<UPostManifestsPullRequest*, UManifestChecksums*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UBasicContentGetContentRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UBasicContentGetContentRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UBasicContentGetContentRequest, UContentOrText>(
	const int64&, UBasicContentGetContentRequest*, FOnBasicContentGetContentSuccess, FOnBasicContentGetContentError, FOnBasicContentGetContentComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UBasicContentGetContentRequest, UContentOrText>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicContentGetContentRequest*, FOnBasicContentGetContentSuccess, FOnBasicContentGetContentError, FOnBasicContentGetContentComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UBasicContentGetContentRequest*, TBeamFullResponseHandler<UBasicContentGetContentRequest*, UContentOrText*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicContentGetContentRequest*,
                                                                                   TBeamFullResponseHandler<UBasicContentGetContentRequest*, UContentOrText*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetLocalizationsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetLocalizationsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetLocalizationsRequest, UGetLocalizationsResponse>(
	const int64&, UGetLocalizationsRequest*, FOnGetLocalizationsSuccess, FOnGetLocalizationsError, FOnGetLocalizationsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetLocalizationsRequest, UGetLocalizationsResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetLocalizationsRequest*, FOnGetLocalizationsSuccess, FOnGetLocalizationsError, FOnGetLocalizationsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetLocalizationsRequest*, TBeamFullResponseHandler<UGetLocalizationsRequest*, UGetLocalizationsResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetLocalizationsRequest*,
                                                                                   TBeamFullResponseHandler<UGetLocalizationsRequest*, UGetLocalizationsResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutLocalizationsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutLocalizationsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutLocalizationsRequest, UCommonResponse>(
	const int64&, UPutLocalizationsRequest*, FOnPutLocalizationsSuccess, FOnPutLocalizationsError, FOnPutLocalizationsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutLocalizationsRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutLocalizationsRequest*, FOnPutLocalizationsSuccess, FOnPutLocalizationsError, FOnPutLocalizationsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutLocalizationsRequest*, TBeamFullResponseHandler<UPutLocalizationsRequest*, UCommonResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutLocalizationsRequest*,
                                                                                   TBeamFullResponseHandler<UPutLocalizationsRequest*, UCommonResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UDeleteLocalizationsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UDeleteLocalizationsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UDeleteLocalizationsRequest, UCommonResponse>(
	const int64&, UDeleteLocalizationsRequest*, FOnDeleteLocalizationsSuccess, FOnDeleteLocalizationsError, FOnDeleteLocalizationsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UDeleteLocalizationsRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteLocalizationsRequest*, FOnDeleteLocalizationsSuccess, FOnDeleteLocalizationsError, FOnDeleteLocalizationsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UDeleteLocalizationsRequest*, TBeamFullResponseHandler<UDeleteLocalizationsRequest*, UCommonResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteLocalizationsRequest*,
                                                                                   TBeamFullResponseHandler<UDeleteLocalizationsRequest*, UCommonResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostTextRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostTextRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostTextRequest, USaveTextResponse>(
	const int64&, UPostTextRequest*, FOnPostTextSuccess, FOnPostTextError, FOnPostTextComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostTextRequest, USaveTextResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostTextRequest*, FOnPostTextSuccess, FOnPostTextError, FOnPostTextComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostTextRequest*, TBeamFullResponseHandler<UPostTextRequest*, USaveTextResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostTextRequest*,
                                                                                   TBeamFullResponseHandler<UPostTextRequest*, USaveTextResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetManifestExactRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetManifestExactRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetManifestExactRequest, UContentBasicManifest>(
	const int64&, UGetManifestExactRequest*, FOnGetManifestExactSuccess, FOnGetManifestExactError, FOnGetManifestExactComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetManifestExactRequest, UContentBasicManifest>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetManifestExactRequest*, FOnGetManifestExactSuccess, FOnGetManifestExactError, FOnGetManifestExactComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetManifestExactRequest*, TBeamFullResponseHandler<UGetManifestExactRequest*, UContentBasicManifest*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetManifestExactRequest*,
                                                                                   TBeamFullResponseHandler<UGetManifestExactRequest*, UContentBasicManifest*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UBasicContentGetManifestRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UBasicContentGetManifestRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UBasicContentGetManifestRequest, UContentBasicManifest>(
	const int64&, UBasicContentGetManifestRequest*, FOnBasicContentGetManifestSuccess, FOnBasicContentGetManifestError, FOnBasicContentGetManifestComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UBasicContentGetManifestRequest, UContentBasicManifest>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicContentGetManifestRequest*, FOnBasicContentGetManifestSuccess, FOnBasicContentGetManifestError, FOnBasicContentGetManifestComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UBasicContentGetManifestRequest*, TBeamFullResponseHandler<UBasicContentGetManifestRequest*, UContentBasicManifest*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicContentGetManifestRequest*,
                                                                                   TBeamFullResponseHandler<UBasicContentGetManifestRequest*, UContentBasicManifest*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UBasicContentPostManifestRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UBasicContentPostManifestRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UBasicContentPostManifestRequest, UContentBasicManifest>(
	const int64&, UBasicContentPostManifestRequest*, FOnBasicContentPostManifestSuccess, FOnBasicContentPostManifestError, FOnBasicContentPostManifestComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UBasicContentPostManifestRequest, UContentBasicManifest>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicContentPostManifestRequest*, FOnBasicContentPostManifestSuccess, FOnBasicContentPostManifestError, FOnBasicContentPostManifestComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UBasicContentPostManifestRequest*, TBeamFullResponseHandler<UBasicContentPostManifestRequest*, UContentBasicManifest*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicContentPostManifestRequest*,
                                                                                   TBeamFullResponseHandler<UBasicContentPostManifestRequest*, UContentBasicManifest*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostManifestsArchiveRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostManifestsArchiveRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostManifestsArchiveRequest, UEmptyResponse>(
	const int64&, UPostManifestsArchiveRequest*, FOnPostManifestsArchiveSuccess, FOnPostManifestsArchiveError, FOnPostManifestsArchiveComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostManifestsArchiveRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostManifestsArchiveRequest*, FOnPostManifestsArchiveSuccess, FOnPostManifestsArchiveError, FOnPostManifestsArchiveComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostManifestsArchiveRequest*, TBeamFullResponseHandler<UPostManifestsArchiveRequest*, UEmptyResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostManifestsArchiveRequest*,
                                                                                   TBeamFullResponseHandler<UPostManifestsArchiveRequest*, UEmptyResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostContentRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostContentRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostContentRequest, USaveContentResponse>(
	const int64&, UPostContentRequest*, FOnPostContentSuccess, FOnPostContentError, FOnPostContentComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostContentRequest, USaveContentResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostContentRequest*, FOnPostContentSuccess, FOnPostContentError, FOnPostContentComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostContentRequest*, TBeamFullResponseHandler<UPostContentRequest*, USaveContentResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostContentRequest*,
                                                                                   TBeamFullResponseHandler<UPostContentRequest*, USaveContentResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutManifestRepeatRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutManifestRepeatRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutManifestRepeatRequest, UCommonResponse>(
	const int64&, UPutManifestRepeatRequest*, FOnPutManifestRepeatSuccess, FOnPutManifestRepeatError, FOnPutManifestRepeatComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutManifestRepeatRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutManifestRepeatRequest*, FOnPutManifestRepeatSuccess, FOnPutManifestRepeatError, FOnPutManifestRepeatComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutManifestRepeatRequest*, TBeamFullResponseHandler<UPutManifestRepeatRequest*, UCommonResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutManifestRepeatRequest*,
                                                                                   TBeamFullResponseHandler<UPutManifestRepeatRequest*, UCommonResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetManifestPrivateRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetManifestPrivateRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetManifestPrivateRequest, UClientManifestCsvResponse>(
	const int64&, UGetManifestPrivateRequest*, FOnGetManifestPrivateSuccess, FOnGetManifestPrivateError, FOnGetManifestPrivateComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetManifestPrivateRequest, UClientManifestCsvResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetManifestPrivateRequest*, FOnGetManifestPrivateSuccess, FOnGetManifestPrivateError, FOnGetManifestPrivateComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetManifestPrivateRequest*, TBeamFullResponseHandler<UGetManifestPrivateRequest*, UClientManifestCsvResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetManifestPrivateRequest*,
                                                                                   TBeamFullResponseHandler<UGetManifestPrivateRequest*, UClientManifestCsvResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetManifestChecksumsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetManifestChecksumsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetManifestChecksumsRequest, UManifestChecksums>(
	const int64&, UGetManifestChecksumsRequest*, FOnGetManifestChecksumsSuccess, FOnGetManifestChecksumsError, FOnGetManifestChecksumsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetManifestChecksumsRequest, UManifestChecksums>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetManifestChecksumsRequest*, FOnGetManifestChecksumsSuccess, FOnGetManifestChecksumsError, FOnGetManifestChecksumsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetManifestChecksumsRequest*, TBeamFullResponseHandler<UGetManifestChecksumsRequest*, UManifestChecksums*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetManifestChecksumsRequest*,
                                                                                   TBeamFullResponseHandler<UGetManifestChecksumsRequest*, UManifestChecksums*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UBasicContentGetManifestsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UBasicContentGetManifestsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UBasicContentGetManifestsRequest, UGetManifestsResponse>(
	const int64&, UBasicContentGetManifestsRequest*, FOnBasicContentGetManifestsSuccess, FOnBasicContentGetManifestsError, FOnBasicContentGetManifestsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UBasicContentGetManifestsRequest, UGetManifestsResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicContentGetManifestsRequest*, FOnBasicContentGetManifestsSuccess, FOnBasicContentGetManifestsError, FOnBasicContentGetManifestsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UBasicContentGetManifestsRequest*, TBeamFullResponseHandler<UBasicContentGetManifestsRequest*, UGetManifestsResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicContentGetManifestsRequest*,
                                                                                   TBeamFullResponseHandler<UBasicContentGetManifestsRequest*, UGetManifestsResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostMetricsUrlRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostMetricsUrlRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostMetricsUrlRequest, UGetSignedUrlResponse>(
	const int64&, UPostMetricsUrlRequest*, FOnPostMetricsUrlSuccess, FOnPostMetricsUrlError, FOnPostMetricsUrlComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostMetricsUrlRequest, UGetSignedUrlResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostMetricsUrlRequest*, FOnPostMetricsUrlSuccess, FOnPostMetricsUrlError, FOnPostMetricsUrlComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostMetricsUrlRequest*, TBeamFullResponseHandler<UPostMetricsUrlRequest*, UGetSignedUrlResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostMetricsUrlRequest*,
                                                                                   TBeamFullResponseHandler<UPostMetricsUrlRequest*, UGetSignedUrlResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetStoragePerformanceRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetStoragePerformanceRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetStoragePerformanceRequest, UPerformanceResponse>(
	const int64&, UGetStoragePerformanceRequest*, FOnGetStoragePerformanceSuccess, FOnGetStoragePerformanceError, FOnGetStoragePerformanceComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetStoragePerformanceRequest, UPerformanceResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetStoragePerformanceRequest*, FOnGetStoragePerformanceSuccess, FOnGetStoragePerformanceError, FOnGetStoragePerformanceComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetStoragePerformanceRequest*, TBeamFullResponseHandler<UGetStoragePerformanceRequest*, UPerformanceResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetStoragePerformanceRequest*,
                                                                                   TBeamFullResponseHandler<UGetStoragePerformanceRequest*, UPerformanceResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UBasicBeamoGetManifestsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UBasicBeamoGetManifestsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UBasicBeamoGetManifestsRequest, UGetManifestsResponse>(
	const int64&, UBasicBeamoGetManifestsRequest*, FOnBasicBeamoGetManifestsSuccess, FOnBasicBeamoGetManifestsError, FOnBasicBeamoGetManifestsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UBasicBeamoGetManifestsRequest, UGetManifestsResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicBeamoGetManifestsRequest*, FOnBasicBeamoGetManifestsSuccess, FOnBasicBeamoGetManifestsError, FOnBasicBeamoGetManifestsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UBasicBeamoGetManifestsRequest*, TBeamFullResponseHandler<UBasicBeamoGetManifestsRequest*, UGetManifestsResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicBeamoGetManifestsRequest*,
                                                                                   TBeamFullResponseHandler<UBasicBeamoGetManifestsRequest*, UGetManifestsResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetTemplatesRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetTemplatesRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetTemplatesRequest, UGetTemplatesResponse>(
	const int64&, UGetTemplatesRequest*, FOnGetTemplatesSuccess, FOnGetTemplatesError, FOnGetTemplatesComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetTemplatesRequest, UGetTemplatesResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetTemplatesRequest*, FOnGetTemplatesSuccess, FOnGetTemplatesError, FOnGetTemplatesComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetTemplatesRequest*, TBeamFullResponseHandler<UGetTemplatesRequest*, UGetTemplatesResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetTemplatesRequest*,
                                                                                   TBeamFullResponseHandler<UGetTemplatesRequest*, UGetTemplatesResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostLogsUrlRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostLogsUrlRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostLogsUrlRequest, UGetSignedUrlResponse>(
	const int64&, UPostLogsUrlRequest*, FOnPostLogsUrlSuccess, FOnPostLogsUrlError, FOnPostLogsUrlComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostLogsUrlRequest, UGetSignedUrlResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostLogsUrlRequest*, FOnPostLogsUrlSuccess, FOnPostLogsUrlError, FOnPostLogsUrlComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostLogsUrlRequest*, TBeamFullResponseHandler<UPostLogsUrlRequest*, UGetSignedUrlResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostLogsUrlRequest*,
                                                                                   TBeamFullResponseHandler<UPostLogsUrlRequest*, UGetSignedUrlResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetUploadAPIRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetUploadAPIRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetUploadAPIRequest, UGetLambdaURI>(
	const int64&, UGetUploadAPIRequest*, FOnGetUploadAPISuccess, FOnGetUploadAPIError, FOnGetUploadAPIComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetUploadAPIRequest, UGetLambdaURI>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetUploadAPIRequest*, FOnGetUploadAPISuccess, FOnGetUploadAPIError, FOnGetUploadAPIComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetUploadAPIRequest*, TBeamFullResponseHandler<UGetUploadAPIRequest*, UGetLambdaURI*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetUploadAPIRequest*,
                                                                                   TBeamFullResponseHandler<UGetUploadAPIRequest*, UGetLambdaURI*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetStatusRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetStatusRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetStatusRequest, UGetStatusResponse>(
	const int64&, UGetStatusRequest*, FOnGetStatusSuccess, FOnGetStatusError, FOnGetStatusComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetStatusRequest, UGetStatusResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetStatusRequest*, FOnGetStatusSuccess, FOnGetStatusError, FOnGetStatusComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetStatusRequest*, TBeamFullResponseHandler<UGetStatusRequest*, UGetStatusResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetStatusRequest*,
                                                                                   TBeamFullResponseHandler<UGetStatusRequest*, UGetStatusResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetManifestCurrentRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetManifestCurrentRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetManifestCurrentRequest, UGetCurrentManifestResponse>(
	const int64&, UGetManifestCurrentRequest*, FOnGetManifestCurrentSuccess, FOnGetManifestCurrentError, FOnGetManifestCurrentComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetManifestCurrentRequest, UGetCurrentManifestResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetManifestCurrentRequest*, FOnGetManifestCurrentSuccess, FOnGetManifestCurrentError, FOnGetManifestCurrentComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetManifestCurrentRequest*, TBeamFullResponseHandler<UGetManifestCurrentRequest*, UGetCurrentManifestResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetManifestCurrentRequest*,
                                                                                   TBeamFullResponseHandler<UGetManifestCurrentRequest*, UGetCurrentManifestResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UBasicBeamoPostManifestPullRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UBasicBeamoPostManifestPullRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UBasicBeamoPostManifestPullRequest, UManifestChecksums>(
	const int64&, UBasicBeamoPostManifestPullRequest*, FOnBasicBeamoPostManifestPullSuccess, FOnBasicBeamoPostManifestPullError, FOnBasicBeamoPostManifestPullComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UBasicBeamoPostManifestPullRequest, UManifestChecksums>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicBeamoPostManifestPullRequest*, FOnBasicBeamoPostManifestPullSuccess, FOnBasicBeamoPostManifestPullError, FOnBasicBeamoPostManifestPullComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UBasicBeamoPostManifestPullRequest*, TBeamFullResponseHandler<UBasicBeamoPostManifestPullRequest*, UManifestChecksums*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicBeamoPostManifestPullRequest*,
                                                                                   TBeamFullResponseHandler<UBasicBeamoPostManifestPullRequest*, UManifestChecksums*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetRegistryRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetRegistryRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetRegistryRequest, UGetElasticContainerRegistryURI>(
	const int64&, UGetRegistryRequest*, FOnGetRegistrySuccess, FOnGetRegistryError, FOnGetRegistryComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetRegistryRequest, UGetElasticContainerRegistryURI>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetRegistryRequest*, FOnGetRegistrySuccess, FOnGetRegistryError, FOnGetRegistryComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetRegistryRequest*, TBeamFullResponseHandler<UGetRegistryRequest*, UGetElasticContainerRegistryURI*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetRegistryRequest*,
                                                                                   TBeamFullResponseHandler<UGetRegistryRequest*, UGetElasticContainerRegistryURI*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostManifestDeployRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostManifestDeployRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostManifestDeployRequest, UEmptyResponse>(
	const int64&, UPostManifestDeployRequest*, FOnPostManifestDeploySuccess, FOnPostManifestDeployError, FOnPostManifestDeployComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostManifestDeployRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostManifestDeployRequest*, FOnPostManifestDeploySuccess, FOnPostManifestDeployError, FOnPostManifestDeployComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostManifestDeployRequest*, TBeamFullResponseHandler<UPostManifestDeployRequest*, UEmptyResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostManifestDeployRequest*,
                                                                                   TBeamFullResponseHandler<UPostManifestDeployRequest*, UEmptyResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetStorageConnectionRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetStorageConnectionRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetStorageConnectionRequest, UConnectionString>(
	const int64&, UGetStorageConnectionRequest*, FOnGetStorageConnectionSuccess, FOnGetStorageConnectionError, FOnGetStorageConnectionComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetStorageConnectionRequest, UConnectionString>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetStorageConnectionRequest*, FOnGetStorageConnectionSuccess, FOnGetStorageConnectionError, FOnGetStorageConnectionComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetStorageConnectionRequest*, TBeamFullResponseHandler<UGetStorageConnectionRequest*, UConnectionString*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetStorageConnectionRequest*,
                                                                                   TBeamFullResponseHandler<UGetStorageConnectionRequest*, UConnectionString*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UBasicBeamoGetManifestRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UBasicBeamoGetManifestRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UBasicBeamoGetManifestRequest, UGetManifestResponse>(
	const int64&, UBasicBeamoGetManifestRequest*, FOnBasicBeamoGetManifestSuccess, FOnBasicBeamoGetManifestError, FOnBasicBeamoGetManifestComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UBasicBeamoGetManifestRequest, UGetManifestResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicBeamoGetManifestRequest*, FOnBasicBeamoGetManifestSuccess, FOnBasicBeamoGetManifestError, FOnBasicBeamoGetManifestComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UBasicBeamoGetManifestRequest*, TBeamFullResponseHandler<UBasicBeamoGetManifestRequest*, UGetManifestResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicBeamoGetManifestRequest*,
                                                                                   TBeamFullResponseHandler<UBasicBeamoGetManifestRequest*, UGetManifestResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UBasicBeamoPostManifestRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UBasicBeamoPostManifestRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UBasicBeamoPostManifestRequest, UPostManifestResponse>(
	const int64&, UBasicBeamoPostManifestRequest*, FOnBasicBeamoPostManifestSuccess, FOnBasicBeamoPostManifestError, FOnBasicBeamoPostManifestComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UBasicBeamoPostManifestRequest, UPostManifestResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicBeamoPostManifestRequest*, FOnBasicBeamoPostManifestSuccess, FOnBasicBeamoPostManifestError, FOnBasicBeamoPostManifestComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UBasicBeamoPostManifestRequest*, TBeamFullResponseHandler<UBasicBeamoPostManifestRequest*, UPostManifestResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicBeamoPostManifestRequest*,
                                                                                   TBeamFullResponseHandler<UBasicBeamoPostManifestRequest*, UPostManifestResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetEventPlayersRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetEventPlayersRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetEventPlayersRequest, UEventPlayerView>(
	const int64&, UGetEventPlayersRequest*, FOnGetEventPlayersSuccess, FOnGetEventPlayersError, FOnGetEventPlayersComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetEventPlayersRequest, UEventPlayerView>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetEventPlayersRequest*, FOnGetEventPlayersSuccess, FOnGetEventPlayersError, FOnGetEventPlayersComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetEventPlayersRequest*, TBeamFullResponseHandler<UGetEventPlayersRequest*, UEventPlayerView*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetEventPlayersRequest*,
                                                                                   TBeamFullResponseHandler<UGetEventPlayersRequest*, UEventPlayerView*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UObjectEventPlayersPostClaimRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UObjectEventPlayersPostClaimRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UObjectEventPlayersPostClaimRequest, UEventClaimResponse>(
	const int64&, UObjectEventPlayersPostClaimRequest*, FOnObjectEventPlayersPostClaimSuccess, FOnObjectEventPlayersPostClaimError, FOnObjectEventPlayersPostClaimComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UObjectEventPlayersPostClaimRequest, UEventClaimResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UObjectEventPlayersPostClaimRequest*, FOnObjectEventPlayersPostClaimSuccess, FOnObjectEventPlayersPostClaimError, FOnObjectEventPlayersPostClaimComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UObjectEventPlayersPostClaimRequest*, TBeamFullResponseHandler<UObjectEventPlayersPostClaimRequest*, UEventClaimResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UObjectEventPlayersPostClaimRequest*,
                                                                                   TBeamFullResponseHandler<UObjectEventPlayersPostClaimRequest*, UEventClaimResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutScoreRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutScoreRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutScoreRequest, UCommonResponse>(
	const int64&, UPutScoreRequest*, FOnPutScoreSuccess, FOnPutScoreError, FOnPutScoreComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutScoreRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutScoreRequest*, FOnPutScoreSuccess, FOnPutScoreError, FOnPutScoreComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutScoreRequest*, TBeamFullResponseHandler<UPutScoreRequest*, UCommonResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutScoreRequest*,
                                                                                   TBeamFullResponseHandler<UPutScoreRequest*, UCommonResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetRunningRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetRunningRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetRunningRequest, UEventQueryResponse>(
	const int64&, UGetRunningRequest*, FOnGetRunningSuccess, FOnGetRunningError, FOnGetRunningComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetRunningRequest, UEventQueryResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetRunningRequest*, FOnGetRunningSuccess, FOnGetRunningError, FOnGetRunningComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetRunningRequest*, TBeamFullResponseHandler<UGetRunningRequest*, UEventQueryResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetRunningRequest*,
                                                                                   TBeamFullResponseHandler<UGetRunningRequest*, UEventQueryResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UBasicEventsGetContentRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UBasicEventsGetContentRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UBasicEventsGetContentRequest, UEventContentResponse>(
	const int64&, UBasicEventsGetContentRequest*, FOnBasicEventsGetContentSuccess, FOnBasicEventsGetContentError, FOnBasicEventsGetContentComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UBasicEventsGetContentRequest, UEventContentResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicEventsGetContentRequest*, FOnBasicEventsGetContentSuccess, FOnBasicEventsGetContentError, FOnBasicEventsGetContentComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UBasicEventsGetContentRequest*, TBeamFullResponseHandler<UBasicEventsGetContentRequest*, UEventContentResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicEventsGetContentRequest*,
                                                                                   TBeamFullResponseHandler<UBasicEventsGetContentRequest*, UEventContentResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetCalendarRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetCalendarRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetCalendarRequest, UEventsInDateRangeResponse>(
	const int64&, UGetCalendarRequest*, FOnGetCalendarSuccess, FOnGetCalendarError, FOnGetCalendarComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetCalendarRequest, UEventsInDateRangeResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetCalendarRequest*, FOnGetCalendarSuccess, FOnGetCalendarError, FOnGetCalendarComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetCalendarRequest*, TBeamFullResponseHandler<UGetCalendarRequest*, UEventsInDateRangeResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetCalendarRequest*,
                                                                                   TBeamFullResponseHandler<UGetCalendarRequest*, UEventsInDateRangeResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostApplyContentRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostApplyContentRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostApplyContentRequest, UCommonResponse>(
	const int64&, UPostApplyContentRequest*, FOnPostApplyContentSuccess, FOnPostApplyContentError, FOnPostApplyContentComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostApplyContentRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostApplyContentRequest*, FOnPostApplyContentSuccess, FOnPostApplyContentError, FOnPostApplyContentComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostApplyContentRequest*, TBeamFullResponseHandler<UPostApplyContentRequest*, UCommonResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostApplyContentRequest*,
                                                                                   TBeamFullResponseHandler<UPostApplyContentRequest*, UCommonResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutEndPhaseRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutEndPhaseRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutEndPhaseRequest, UCommonResponse>(
	const int64&, UPutEndPhaseRequest*, FOnPutEndPhaseSuccess, FOnPutEndPhaseError, FOnPutEndPhaseComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutEndPhaseRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutEndPhaseRequest*, FOnPutEndPhaseSuccess, FOnPutEndPhaseError, FOnPutEndPhaseComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutEndPhaseRequest*, TBeamFullResponseHandler<UPutEndPhaseRequest*, UCommonResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutEndPhaseRequest*,
                                                                                   TBeamFullResponseHandler<UPutEndPhaseRequest*, UCommonResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetEventsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetEventsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetEventsRequest, UEventObjectData>(
	const int64&, UGetEventsRequest*, FOnGetEventsSuccess, FOnGetEventsError, FOnGetEventsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetEventsRequest, UEventObjectData>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetEventsRequest*, FOnGetEventsSuccess, FOnGetEventsError, FOnGetEventsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetEventsRequest*, TBeamFullResponseHandler<UGetEventsRequest*, UEventObjectData*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetEventsRequest*,
                                                                                   TBeamFullResponseHandler<UGetEventsRequest*, UEventObjectData*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetPingRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetPingRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetPingRequest, UPingRsp>(
	const int64&, UGetPingRequest*, FOnGetPingSuccess, FOnGetPingError, FOnGetPingComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetPingRequest, UPingRsp>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetPingRequest*, FOnGetPingSuccess, FOnGetPingError, FOnGetPingComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetPingRequest*, TBeamFullResponseHandler<UGetPingRequest*, UPingRsp*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetPingRequest*,
                                                                                   TBeamFullResponseHandler<UGetPingRequest*, UPingRsp*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutContentRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutContentRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutContentRequest, UCommonResponse>(
	const int64&, UPutContentRequest*, FOnPutContentSuccess, FOnPutContentError, FOnPutContentComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutContentRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutContentRequest*, FOnPutContentSuccess, FOnPutContentError, FOnPutContentComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutContentRequest*, TBeamFullResponseHandler<UPutContentRequest*, UCommonResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutContentRequest*,
                                                                                   TBeamFullResponseHandler<UPutContentRequest*, UCommonResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UDeleteContentRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UDeleteContentRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UDeleteContentRequest, UCommonResponse>(
	const int64&, UDeleteContentRequest*, FOnDeleteContentSuccess, FOnDeleteContentError, FOnDeleteContentComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UDeleteContentRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteContentRequest*, FOnDeleteContentSuccess, FOnDeleteContentError, FOnDeleteContentComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UDeleteContentRequest*, TBeamFullResponseHandler<UDeleteContentRequest*, UCommonResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteContentRequest*,
                                                                                   TBeamFullResponseHandler<UDeleteContentRequest*, UCommonResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutRefreshRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutRefreshRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutRefreshRequest, UCommonResponse>(
	const int64&, UPutRefreshRequest*, FOnPutRefreshSuccess, FOnPutRefreshError, FOnPutRefreshComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutRefreshRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutRefreshRequest*, FOnPutRefreshSuccess, FOnPutRefreshError, FOnPutRefreshComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutRefreshRequest*, TBeamFullResponseHandler<UPutRefreshRequest*, UCommonResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutRefreshRequest*,
                                                                                   TBeamFullResponseHandler<UPutRefreshRequest*, UCommonResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetAvailabilityRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetAvailabilityRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetAvailabilityRequest, UAvailabilityResponse>(
	const int64&, UGetAvailabilityRequest*, FOnGetAvailabilitySuccess, FOnGetAvailabilityError, FOnGetAvailabilityComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetAvailabilityRequest, UAvailabilityResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetAvailabilityRequest*, FOnGetAvailabilitySuccess, FOnGetAvailabilityError, FOnGetAvailabilityComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetAvailabilityRequest*, TBeamFullResponseHandler<UGetAvailabilityRequest*, UAvailabilityResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetAvailabilityRequest*,
                                                                                   TBeamFullResponseHandler<UGetAvailabilityRequest*, UAvailabilityResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetRecommendedRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetRecommendedRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetRecommendedRequest, UGroupSearchResponse>(
	const int64&, UGetRecommendedRequest*, FOnGetRecommendedSuccess, FOnGetRecommendedError, FOnGetRecommendedComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetRecommendedRequest, UGroupSearchResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetRecommendedRequest*, FOnGetRecommendedSuccess, FOnGetRecommendedError, FOnGetRecommendedComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetRecommendedRequest*, TBeamFullResponseHandler<UGetRecommendedRequest*, UGroupSearchResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetRecommendedRequest*,
                                                                                   TBeamFullResponseHandler<UGetRecommendedRequest*, UGroupSearchResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostJoinRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostJoinRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostJoinRequest, UGroupMembershipResponse>(
	const int64&, UPostJoinRequest*, FOnPostJoinSuccess, FOnPostJoinError, FOnPostJoinComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostJoinRequest, UGroupMembershipResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostJoinRequest*, FOnPostJoinSuccess, FOnPostJoinError, FOnPostJoinComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostJoinRequest*, TBeamFullResponseHandler<UPostJoinRequest*, UGroupMembershipResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostJoinRequest*,
                                                                                   TBeamFullResponseHandler<UPostJoinRequest*, UGroupMembershipResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UDeleteJoinRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UDeleteJoinRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UDeleteJoinRequest, UGroupMembershipResponse>(
	const int64&, UDeleteJoinRequest*, FOnDeleteJoinSuccess, FOnDeleteJoinError, FOnDeleteJoinComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UDeleteJoinRequest, UGroupMembershipResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteJoinRequest*, FOnDeleteJoinSuccess, FOnDeleteJoinError, FOnDeleteJoinComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UDeleteJoinRequest*, TBeamFullResponseHandler<UDeleteJoinRequest*, UGroupMembershipResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteJoinRequest*,
                                                                                   TBeamFullResponseHandler<UDeleteJoinRequest*, UGroupMembershipResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostGroupRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostGroupRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostGroupRequest, UGroupCreateResponse>(
	const int64&, UPostGroupRequest*, FOnPostGroupSuccess, FOnPostGroupError, FOnPostGroupComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostGroupRequest, UGroupCreateResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostGroupRequest*, FOnPostGroupSuccess, FOnPostGroupError, FOnPostGroupComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostGroupRequest*, TBeamFullResponseHandler<UPostGroupRequest*, UGroupCreateResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostGroupRequest*,
                                                                                   TBeamFullResponseHandler<UPostGroupRequest*, UGroupCreateResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UObjectGroupUsersGetSearchRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UObjectGroupUsersGetSearchRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UObjectGroupUsersGetSearchRequest, UGroupSearchResponse>(
	const int64&, UObjectGroupUsersGetSearchRequest*, FOnObjectGroupUsersGetSearchSuccess, FOnObjectGroupUsersGetSearchError, FOnObjectGroupUsersGetSearchComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UObjectGroupUsersGetSearchRequest, UGroupSearchResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UObjectGroupUsersGetSearchRequest*, FOnObjectGroupUsersGetSearchSuccess, FOnObjectGroupUsersGetSearchError, FOnObjectGroupUsersGetSearchComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UObjectGroupUsersGetSearchRequest*, TBeamFullResponseHandler<UObjectGroupUsersGetSearchRequest*, UGroupSearchResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UObjectGroupUsersGetSearchRequest*,
                                                                                   TBeamFullResponseHandler<UObjectGroupUsersGetSearchRequest*, UGroupSearchResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetGroupUsersRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetGroupUsersRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetGroupUsersRequest, UGroupUser>(
	const int64&, UGetGroupUsersRequest*, FOnGetGroupUsersSuccess, FOnGetGroupUsersError, FOnGetGroupUsersComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetGroupUsersRequest, UGroupUser>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetGroupUsersRequest*, FOnGetGroupUsersSuccess, FOnGetGroupUsersError, FOnGetGroupUsersComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetGroupUsersRequest*, TBeamFullResponseHandler<UGetGroupUsersRequest*, UGroupUser*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetGroupUsersRequest*,
                                                                                   TBeamFullResponseHandler<UGetGroupUsersRequest*, UGroupUser*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostKickRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostKickRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostKickRequest, UGroupMembershipResponse>(
	const int64&, UPostKickRequest*, FOnPostKickSuccess, FOnPostKickError, FOnPostKickComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostKickRequest, UGroupMembershipResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostKickRequest*, FOnPostKickSuccess, FOnPostKickError, FOnPostKickComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostKickRequest*, TBeamFullResponseHandler<UPostKickRequest*, UGroupMembershipResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostKickRequest*,
                                                                                   TBeamFullResponseHandler<UPostKickRequest*, UGroupMembershipResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UDeleteMemberRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UDeleteMemberRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UDeleteMemberRequest, UGroupMembershipResponse>(
	const int64&, UDeleteMemberRequest*, FOnDeleteMemberSuccess, FOnDeleteMemberError, FOnDeleteMemberComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UDeleteMemberRequest, UGroupMembershipResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteMemberRequest*, FOnDeleteMemberSuccess, FOnDeleteMemberError, FOnDeleteMemberComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UDeleteMemberRequest*, TBeamFullResponseHandler<UDeleteMemberRequest*, UGroupMembershipResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteMemberRequest*,
                                                                                   TBeamFullResponseHandler<UDeleteMemberRequest*, UGroupMembershipResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UObjectGroupsGetGroupsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UObjectGroupsGetGroupsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UObjectGroupsGetGroupsRequest, UGroup>(
	const int64&, UObjectGroupsGetGroupsRequest*, FOnObjectGroupsGetGroupsSuccess, FOnObjectGroupsGetGroupsError, FOnObjectGroupsGetGroupsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UObjectGroupsGetGroupsRequest, UGroup>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UObjectGroupsGetGroupsRequest*, FOnObjectGroupsGetGroupsSuccess, FOnObjectGroupsGetGroupsError, FOnObjectGroupsGetGroupsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UObjectGroupsGetGroupsRequest*, TBeamFullResponseHandler<UObjectGroupsGetGroupsRequest*, UGroup*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UObjectGroupsGetGroupsRequest*,
                                                                                   TBeamFullResponseHandler<UObjectGroupsGetGroupsRequest*, UGroup*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutGroupsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutGroupsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutGroupsRequest, UCommonResponse>(
	const int64&, UPutGroupsRequest*, FOnPutGroupsSuccess, FOnPutGroupsError, FOnPutGroupsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutGroupsRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutGroupsRequest*, FOnPutGroupsSuccess, FOnPutGroupsError, FOnPutGroupsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutGroupsRequest*, TBeamFullResponseHandler<UPutGroupsRequest*, UCommonResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutGroupsRequest*,
                                                                                   TBeamFullResponseHandler<UPutGroupsRequest*, UCommonResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UDeleteGroupsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UDeleteGroupsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UDeleteGroupsRequest, UCommonResponse>(
	const int64&, UDeleteGroupsRequest*, FOnDeleteGroupsSuccess, FOnDeleteGroupsError, FOnDeleteGroupsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UDeleteGroupsRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteGroupsRequest*, FOnDeleteGroupsSuccess, FOnDeleteGroupsError, FOnDeleteGroupsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UDeleteGroupsRequest*, TBeamFullResponseHandler<UDeleteGroupsRequest*, UCommonResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteGroupsRequest*,
                                                                                   TBeamFullResponseHandler<UDeleteGroupsRequest*, UCommonResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UObjectGroupsPutRoleRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UObjectGroupsPutRoleRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UObjectGroupsPutRoleRequest, UCommonResponse>(
	const int64&, UObjectGroupsPutRoleRequest*, FOnObjectGroupsPutRoleSuccess, FOnObjectGroupsPutRoleError, FOnObjectGroupsPutRoleComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UObjectGroupsPutRoleRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UObjectGroupsPutRoleRequest*, FOnObjectGroupsPutRoleSuccess, FOnObjectGroupsPutRoleError, FOnObjectGroupsPutRoleComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UObjectGroupsPutRoleRequest*, TBeamFullResponseHandler<UObjectGroupsPutRoleRequest*, UCommonResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UObjectGroupsPutRoleRequest*,
                                                                                   TBeamFullResponseHandler<UObjectGroupsPutRoleRequest*, UCommonResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostApplyRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostApplyRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostApplyRequest, UCommonResponse>(
	const int64&, UPostApplyRequest*, FOnPostApplySuccess, FOnPostApplyError, FOnPostApplyComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostApplyRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostApplyRequest*, FOnPostApplySuccess, FOnPostApplyError, FOnPostApplyComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostApplyRequest*, TBeamFullResponseHandler<UPostApplyRequest*, UCommonResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostApplyRequest*,
                                                                                   TBeamFullResponseHandler<UPostApplyRequest*, UCommonResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostDonationsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostDonationsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostDonationsRequest, UEmptyResponse>(
	const int64&, UPostDonationsRequest*, FOnPostDonationsSuccess, FOnPostDonationsError, FOnPostDonationsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostDonationsRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostDonationsRequest*, FOnPostDonationsSuccess, FOnPostDonationsError, FOnPostDonationsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostDonationsRequest*, TBeamFullResponseHandler<UPostDonationsRequest*, UEmptyResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostDonationsRequest*,
                                                                                   TBeamFullResponseHandler<UPostDonationsRequest*, UEmptyResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutDonationsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutDonationsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutDonationsRequest, UEmptyResponse>(
	const int64&, UPutDonationsRequest*, FOnPutDonationsSuccess, FOnPutDonationsError, FOnPutDonationsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutDonationsRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutDonationsRequest*, FOnPutDonationsSuccess, FOnPutDonationsError, FOnPutDonationsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutDonationsRequest*, TBeamFullResponseHandler<UPutDonationsRequest*, UEmptyResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutDonationsRequest*,
                                                                                   TBeamFullResponseHandler<UPutDonationsRequest*, UEmptyResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutDonationsClaimRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutDonationsClaimRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutDonationsClaimRequest, UEmptyResponse>(
	const int64&, UPutDonationsClaimRequest*, FOnPutDonationsClaimSuccess, FOnPutDonationsClaimError, FOnPutDonationsClaimComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutDonationsClaimRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutDonationsClaimRequest*, FOnPutDonationsClaimSuccess, FOnPutDonationsClaimError, FOnPutDonationsClaimComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutDonationsClaimRequest*, TBeamFullResponseHandler<UPutDonationsClaimRequest*, UEmptyResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutDonationsClaimRequest*,
                                                                                   TBeamFullResponseHandler<UPutDonationsClaimRequest*, UEmptyResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostInviteRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostInviteRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostInviteRequest, UCommonResponse>(
	const int64&, UPostInviteRequest*, FOnPostInviteSuccess, FOnPostInviteError, FOnPostInviteComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostInviteRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostInviteRequest*, FOnPostInviteSuccess, FOnPostInviteError, FOnPostInviteComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostInviteRequest*, TBeamFullResponseHandler<UPostInviteRequest*, UCommonResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostInviteRequest*,
                                                                                   TBeamFullResponseHandler<UPostInviteRequest*, UCommonResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostPetitionRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostPetitionRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostPetitionRequest, UCommonResponse>(
	const int64&, UPostPetitionRequest*, FOnPostPetitionSuccess, FOnPostPetitionError, FOnPostPetitionComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostPetitionRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostPetitionRequest*, FOnPostPetitionSuccess, FOnPostPetitionError, FOnPostPetitionComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostPetitionRequest*, TBeamFullResponseHandler<UPostPetitionRequest*, UCommonResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostPetitionRequest*,
                                                                                   TBeamFullResponseHandler<UPostPetitionRequest*, UCommonResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetItemsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetItemsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetItemsRequest, UItemContentResponse>(
	const int64&, UGetItemsRequest*, FOnGetItemsSuccess, FOnGetItemsError, FOnGetItemsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetItemsRequest, UItemContentResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetItemsRequest*, FOnGetItemsSuccess, FOnGetItemsError, FOnGetItemsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetItemsRequest*, TBeamFullResponseHandler<UGetItemsRequest*, UItemContentResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetItemsRequest*,
                                                                                   TBeamFullResponseHandler<UGetItemsRequest*, UItemContentResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetCurrencyRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetCurrencyRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetCurrencyRequest, UCurrencyContentResponse>(
	const int64&, UGetCurrencyRequest*, FOnGetCurrencySuccess, FOnGetCurrencyError, FOnGetCurrencyComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetCurrencyRequest, UCurrencyContentResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetCurrencyRequest*, FOnGetCurrencySuccess, FOnGetCurrencyError, FOnGetCurrencyComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetCurrencyRequest*, TBeamFullResponseHandler<UGetCurrencyRequest*, UCurrencyContentResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetCurrencyRequest*,
                                                                                   TBeamFullResponseHandler<UGetCurrencyRequest*, UCurrencyContentResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutPreviewRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutPreviewRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutPreviewRequest, UPreviewVipBonusResponse>(
	const int64&, UPutPreviewRequest*, FOnPutPreviewSuccess, FOnPutPreviewError, FOnPutPreviewComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutPreviewRequest, UPreviewVipBonusResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutPreviewRequest*, FOnPutPreviewSuccess, FOnPutPreviewError, FOnPutPreviewComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutPreviewRequest*, TBeamFullResponseHandler<UPutPreviewRequest*, UPreviewVipBonusResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutPreviewRequest*,
                                                                                   TBeamFullResponseHandler<UPutPreviewRequest*, UPreviewVipBonusResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetMultipliersRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetMultipliersRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetMultipliersRequest, UMultipliersGetResponse>(
	const int64&, UGetMultipliersRequest*, FOnGetMultipliersSuccess, FOnGetMultipliersError, FOnGetMultipliersComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetMultipliersRequest, UMultipliersGetResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetMultipliersRequest*, FOnGetMultipliersSuccess, FOnGetMultipliersError, FOnGetMultipliersComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetMultipliersRequest*, TBeamFullResponseHandler<UGetMultipliersRequest*, UMultipliersGetResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetMultipliersRequest*,
                                                                                   TBeamFullResponseHandler<UGetMultipliersRequest*, UMultipliersGetResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetInventoryRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetInventoryRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetInventoryRequest, UInventoryView>(
	const int64&, UGetInventoryRequest*, FOnGetInventorySuccess, FOnGetInventoryError, FOnGetInventoryComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetInventoryRequest, UInventoryView>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetInventoryRequest*, FOnGetInventorySuccess, FOnGetInventoryError, FOnGetInventoryComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetInventoryRequest*, TBeamFullResponseHandler<UGetInventoryRequest*, UInventoryView*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetInventoryRequest*,
                                                                                   TBeamFullResponseHandler<UGetInventoryRequest*, UInventoryView*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostInventoryRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostInventoryRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostInventoryRequest, UInventoryView>(
	const int64&, UPostInventoryRequest*, FOnPostInventorySuccess, FOnPostInventoryError, FOnPostInventoryComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostInventoryRequest, UInventoryView>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostInventoryRequest*, FOnPostInventorySuccess, FOnPostInventoryError, FOnPostInventoryComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostInventoryRequest*, TBeamFullResponseHandler<UPostInventoryRequest*, UInventoryView*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostInventoryRequest*,
                                                                                   TBeamFullResponseHandler<UPostInventoryRequest*, UInventoryView*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutInventoryRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutInventoryRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutInventoryRequest, UCommonResponse>(
	const int64&, UPutInventoryRequest*, FOnPutInventorySuccess, FOnPutInventoryError, FOnPutInventoryComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutInventoryRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutInventoryRequest*, FOnPutInventorySuccess, FOnPutInventoryError, FOnPutInventoryComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutInventoryRequest*, TBeamFullResponseHandler<UPutInventoryRequest*, UCommonResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutInventoryRequest*,
                                                                                   TBeamFullResponseHandler<UPutInventoryRequest*, UCommonResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UDeleteTransactionRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UDeleteTransactionRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UDeleteTransactionRequest, UCommonResponse>(
	const int64&, UDeleteTransactionRequest*, FOnDeleteTransactionSuccess, FOnDeleteTransactionError, FOnDeleteTransactionComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UDeleteTransactionRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteTransactionRequest*, FOnDeleteTransactionSuccess, FOnDeleteTransactionError, FOnDeleteTransactionComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UDeleteTransactionRequest*, TBeamFullResponseHandler<UDeleteTransactionRequest*, UCommonResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteTransactionRequest*,
                                                                                   TBeamFullResponseHandler<UDeleteTransactionRequest*, UCommonResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutTransferRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutTransferRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutTransferRequest, UCommonResponse>(
	const int64&, UPutTransferRequest*, FOnPutTransferSuccess, FOnPutTransferError, FOnPutTransferComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutTransferRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutTransferRequest*, FOnPutTransferSuccess, FOnPutTransferError, FOnPutTransferComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutTransferRequest*, TBeamFullResponseHandler<UPutTransferRequest*, UCommonResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutTransferRequest*,
                                                                                   TBeamFullResponseHandler<UPutTransferRequest*, UCommonResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetRanksRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetRanksRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetRanksRequest, ULeaderBoardViewResponse>(
	const int64&, UGetRanksRequest*, FOnGetRanksSuccess, FOnGetRanksError, FOnGetRanksComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetRanksRequest, ULeaderBoardViewResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetRanksRequest*, FOnGetRanksSuccess, FOnGetRanksError, FOnGetRanksComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetRanksRequest*, TBeamFullResponseHandler<UGetRanksRequest*, ULeaderBoardViewResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetRanksRequest*,
                                                                                   TBeamFullResponseHandler<UGetRanksRequest*, ULeaderBoardViewResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetMatchesRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetMatchesRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetMatchesRequest, UMatchMakingMatchesPvpResponse>(
	const int64&, UGetMatchesRequest*, FOnGetMatchesSuccess, FOnGetMatchesError, FOnGetMatchesComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetMatchesRequest, UMatchMakingMatchesPvpResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetMatchesRequest*, FOnGetMatchesSuccess, FOnGetMatchesError, FOnGetMatchesComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetMatchesRequest*, TBeamFullResponseHandler<UGetMatchesRequest*, UMatchMakingMatchesPvpResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetMatchesRequest*,
                                                                                   TBeamFullResponseHandler<UGetMatchesRequest*, UMatchMakingMatchesPvpResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutEntryRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutEntryRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutEntryRequest, UCommonResponse>(
	const int64&, UPutEntryRequest*, FOnPutEntrySuccess, FOnPutEntryError, FOnPutEntryComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutEntryRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutEntryRequest*, FOnPutEntrySuccess, FOnPutEntryError, FOnPutEntryComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutEntryRequest*, TBeamFullResponseHandler<UPutEntryRequest*, UCommonResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutEntryRequest*,
                                                                                   TBeamFullResponseHandler<UPutEntryRequest*, UCommonResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetViewRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetViewRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetViewRequest, ULeaderBoardViewResponse>(
	const int64&, UGetViewRequest*, FOnGetViewSuccess, FOnGetViewError, FOnGetViewComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetViewRequest, ULeaderBoardViewResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetViewRequest*, FOnGetViewSuccess, FOnGetViewError, FOnGetViewComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetViewRequest*, TBeamFullResponseHandler<UGetViewRequest*, ULeaderBoardViewResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetViewRequest*,
                                                                                   TBeamFullResponseHandler<UGetViewRequest*, ULeaderBoardViewResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UBasicLeaderboardsGetListRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UBasicLeaderboardsGetListRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UBasicLeaderboardsGetListRequest, ULeaderboardListResponse>(
	const int64&, UBasicLeaderboardsGetListRequest*, FOnBasicLeaderboardsGetListSuccess, FOnBasicLeaderboardsGetListError, FOnBasicLeaderboardsGetListComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UBasicLeaderboardsGetListRequest, ULeaderboardListResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicLeaderboardsGetListRequest*, FOnBasicLeaderboardsGetListSuccess, FOnBasicLeaderboardsGetListError, FOnBasicLeaderboardsGetListComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UBasicLeaderboardsGetListRequest*, TBeamFullResponseHandler<UBasicLeaderboardsGetListRequest*, ULeaderboardListResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicLeaderboardsGetListRequest*,
                                                                                   TBeamFullResponseHandler<UBasicLeaderboardsGetListRequest*, ULeaderboardListResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetPlayerRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetPlayerRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetPlayerRequest, UListLeaderBoardViewResponse>(
	const int64&, UGetPlayerRequest*, FOnGetPlayerSuccess, FOnGetPlayerError, FOnGetPlayerComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetPlayerRequest, UListLeaderBoardViewResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetPlayerRequest*, FOnGetPlayerSuccess, FOnGetPlayerError, FOnGetPlayerComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetPlayerRequest*, TBeamFullResponseHandler<UGetPlayerRequest*, UListLeaderBoardViewResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetPlayerRequest*,
                                                                                   TBeamFullResponseHandler<UGetPlayerRequest*, UListLeaderBoardViewResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UBasicLeaderboardsGetAssignmentRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UBasicLeaderboardsGetAssignmentRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UBasicLeaderboardsGetAssignmentRequest, ULeaderboardAssignmentInfo>(
	const int64&, UBasicLeaderboardsGetAssignmentRequest*, FOnBasicLeaderboardsGetAssignmentSuccess, FOnBasicLeaderboardsGetAssignmentError, FOnBasicLeaderboardsGetAssignmentComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UBasicLeaderboardsGetAssignmentRequest, ULeaderboardAssignmentInfo>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicLeaderboardsGetAssignmentRequest*, FOnBasicLeaderboardsGetAssignmentSuccess, FOnBasicLeaderboardsGetAssignmentError, FOnBasicLeaderboardsGetAssignmentComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UBasicLeaderboardsGetAssignmentRequest*, TBeamFullResponseHandler<UBasicLeaderboardsGetAssignmentRequest*, ULeaderboardAssignmentInfo*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicLeaderboardsGetAssignmentRequest*,
                                                                                   TBeamFullResponseHandler<UBasicLeaderboardsGetAssignmentRequest*, ULeaderboardAssignmentInfo*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetUidRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetUidRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetUidRequest, ULeaderboardUidResponse>(
	const int64&, UGetUidRequest*, FOnGetUidSuccess, FOnGetUidError, FOnGetUidComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetUidRequest, ULeaderboardUidResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetUidRequest*, FOnGetUidSuccess, FOnGetUidError, FOnGetUidComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetUidRequest*, TBeamFullResponseHandler<UGetUidRequest*, ULeaderboardUidResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetUidRequest*,
                                                                                   TBeamFullResponseHandler<UGetUidRequest*, ULeaderboardUidResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UDeleteEntriesRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UDeleteEntriesRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UDeleteEntriesRequest, UCommonResponse>(
	const int64&, UDeleteEntriesRequest*, FOnDeleteEntriesSuccess, FOnDeleteEntriesError, FOnDeleteEntriesComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UDeleteEntriesRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteEntriesRequest*, FOnDeleteEntriesSuccess, FOnDeleteEntriesError, FOnDeleteEntriesComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UDeleteEntriesRequest*, TBeamFullResponseHandler<UDeleteEntriesRequest*, UCommonResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteEntriesRequest*,
                                                                                   TBeamFullResponseHandler<UDeleteEntriesRequest*, UCommonResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetMembershipRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetMembershipRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetMembershipRequest, ULeaderboardMembershipResponse>(
	const int64&, UGetMembershipRequest*, FOnGetMembershipSuccess, FOnGetMembershipError, FOnGetMembershipComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetMembershipRequest, ULeaderboardMembershipResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetMembershipRequest*, FOnGetMembershipSuccess, FOnGetMembershipError, FOnGetMembershipComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetMembershipRequest*, TBeamFullResponseHandler<UGetMembershipRequest*, ULeaderboardMembershipResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetMembershipRequest*,
                                                                                   TBeamFullResponseHandler<UGetMembershipRequest*, ULeaderboardMembershipResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetPartitionRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetPartitionRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetPartitionRequest, ULeaderboardPartitionInfo>(
	const int64&, UGetPartitionRequest*, FOnGetPartitionSuccess, FOnGetPartitionError, FOnGetPartitionComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetPartitionRequest, ULeaderboardPartitionInfo>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetPartitionRequest*, FOnGetPartitionSuccess, FOnGetPartitionError, FOnGetPartitionComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetPartitionRequest*, TBeamFullResponseHandler<UGetPartitionRequest*, ULeaderboardPartitionInfo*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetPartitionRequest*,
                                                                                   TBeamFullResponseHandler<UGetPartitionRequest*, ULeaderboardPartitionInfo*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetFriendsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetFriendsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetFriendsRequest, ULeaderBoardViewResponse>(
	const int64&, UGetFriendsRequest*, FOnGetFriendsSuccess, FOnGetFriendsError, FOnGetFriendsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetFriendsRequest, ULeaderBoardViewResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetFriendsRequest*, FOnGetFriendsSuccess, FOnGetFriendsError, FOnGetFriendsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetFriendsRequest*, TBeamFullResponseHandler<UGetFriendsRequest*, ULeaderBoardViewResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetFriendsRequest*,
                                                                                   TBeamFullResponseHandler<UGetFriendsRequest*, ULeaderBoardViewResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostLeaderboardsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostLeaderboardsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostLeaderboardsRequest, UCommonResponse>(
	const int64&, UPostLeaderboardsRequest*, FOnPostLeaderboardsSuccess, FOnPostLeaderboardsError, FOnPostLeaderboardsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostLeaderboardsRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostLeaderboardsRequest*, FOnPostLeaderboardsSuccess, FOnPostLeaderboardsError, FOnPostLeaderboardsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostLeaderboardsRequest*, TBeamFullResponseHandler<UPostLeaderboardsRequest*, UCommonResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostLeaderboardsRequest*,
                                                                                   TBeamFullResponseHandler<UPostLeaderboardsRequest*, UCommonResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UDeleteLeaderboardsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UDeleteLeaderboardsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UDeleteLeaderboardsRequest, UCommonResponse>(
	const int64&, UDeleteLeaderboardsRequest*, FOnDeleteLeaderboardsSuccess, FOnDeleteLeaderboardsError, FOnDeleteLeaderboardsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UDeleteLeaderboardsRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteLeaderboardsRequest*, FOnDeleteLeaderboardsSuccess, FOnDeleteLeaderboardsError, FOnDeleteLeaderboardsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UDeleteLeaderboardsRequest*, TBeamFullResponseHandler<UDeleteLeaderboardsRequest*, UCommonResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteLeaderboardsRequest*,
                                                                                   TBeamFullResponseHandler<UDeleteLeaderboardsRequest*, UCommonResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UObjectLeaderboardsGetAssignmentRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UObjectLeaderboardsGetAssignmentRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UObjectLeaderboardsGetAssignmentRequest, ULeaderboardAssignmentInfo>(
	const int64&, UObjectLeaderboardsGetAssignmentRequest*, FOnObjectLeaderboardsGetAssignmentSuccess, FOnObjectLeaderboardsGetAssignmentError, FOnObjectLeaderboardsGetAssignmentComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UObjectLeaderboardsGetAssignmentRequest, ULeaderboardAssignmentInfo>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UObjectLeaderboardsGetAssignmentRequest*, FOnObjectLeaderboardsGetAssignmentSuccess, FOnObjectLeaderboardsGetAssignmentError, FOnObjectLeaderboardsGetAssignmentComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UObjectLeaderboardsGetAssignmentRequest*, TBeamFullResponseHandler<UObjectLeaderboardsGetAssignmentRequest*, ULeaderboardAssignmentInfo*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UObjectLeaderboardsGetAssignmentRequest*,
                                                                                   TBeamFullResponseHandler<UObjectLeaderboardsGetAssignmentRequest*, ULeaderboardAssignmentInfo*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UDeleteAssignmentRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UDeleteAssignmentRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UDeleteAssignmentRequest, UCommonResponse>(
	const int64&, UDeleteAssignmentRequest*, FOnDeleteAssignmentSuccess, FOnDeleteAssignmentError, FOnDeleteAssignmentComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UDeleteAssignmentRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteAssignmentRequest*, FOnDeleteAssignmentSuccess, FOnDeleteAssignmentError, FOnDeleteAssignmentComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UDeleteAssignmentRequest*, TBeamFullResponseHandler<UDeleteAssignmentRequest*, UCommonResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteAssignmentRequest*,
                                                                                   TBeamFullResponseHandler<UDeleteAssignmentRequest*, UCommonResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UDeleteEntryRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UDeleteEntryRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UDeleteEntryRequest, UCommonResponse>(
	const int64&, UDeleteEntryRequest*, FOnDeleteEntrySuccess, FOnDeleteEntryError, FOnDeleteEntryComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UDeleteEntryRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteEntryRequest*, FOnDeleteEntrySuccess, FOnDeleteEntryError, FOnDeleteEntryComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UDeleteEntryRequest*, TBeamFullResponseHandler<UDeleteEntryRequest*, UCommonResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteEntryRequest*,
                                                                                   TBeamFullResponseHandler<UDeleteEntryRequest*, UCommonResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutFreezeRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutFreezeRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutFreezeRequest, UCommonResponse>(
	const int64&, UPutFreezeRequest*, FOnPutFreezeSuccess, FOnPutFreezeError, FOnPutFreezeComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutFreezeRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutFreezeRequest*, FOnPutFreezeSuccess, FOnPutFreezeError, FOnPutFreezeComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutFreezeRequest*, TBeamFullResponseHandler<UPutFreezeRequest*, UCommonResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutFreezeRequest*,
                                                                                   TBeamFullResponseHandler<UPutFreezeRequest*, UCommonResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetDetailsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetDetailsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetDetailsRequest, ULeaderboardDetails>(
	const int64&, UGetDetailsRequest*, FOnGetDetailsSuccess, FOnGetDetailsError, FOnGetDetailsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetDetailsRequest, ULeaderboardDetails>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetDetailsRequest*, FOnGetDetailsSuccess, FOnGetDetailsError, FOnGetDetailsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetDetailsRequest*, TBeamFullResponseHandler<UGetDetailsRequest*, ULeaderboardDetails*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetDetailsRequest*,
                                                                                   TBeamFullResponseHandler<UGetDetailsRequest*, ULeaderboardDetails*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutSwapRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutSwapRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutSwapRequest, UCommonResponse>(
	const int64&, UPutSwapRequest*, FOnPutSwapSuccess, FOnPutSwapError, FOnPutSwapComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutSwapRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutSwapRequest*, FOnPutSwapSuccess, FOnPutSwapError, FOnPutSwapComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutSwapRequest*, TBeamFullResponseHandler<UPutSwapRequest*, UCommonResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutSwapRequest*,
                                                                                   TBeamFullResponseHandler<UPutSwapRequest*, UCommonResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetGetPersonallyIdentifiableInformationRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetGetPersonallyIdentifiableInformationRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetGetPersonallyIdentifiableInformationRequest, UAccountPersonallyIdentifiableInformationResponse>(
	const int64&, UGetGetPersonallyIdentifiableInformationRequest*, FOnGetGetPersonallyIdentifiableInformationSuccess, FOnGetGetPersonallyIdentifiableInformationError, FOnGetGetPersonallyIdentifiableInformationComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetGetPersonallyIdentifiableInformationRequest, UAccountPersonallyIdentifiableInformationResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetGetPersonallyIdentifiableInformationRequest*, FOnGetGetPersonallyIdentifiableInformationSuccess, FOnGetGetPersonallyIdentifiableInformationError, FOnGetGetPersonallyIdentifiableInformationComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetGetPersonallyIdentifiableInformationRequest*, TBeamFullResponseHandler<UGetGetPersonallyIdentifiableInformationRequest*, UAccountPersonallyIdentifiableInformationResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetGetPersonallyIdentifiableInformationRequest*,
                                                                                   TBeamFullResponseHandler<UGetGetPersonallyIdentifiableInformationRequest*, UAccountPersonallyIdentifiableInformationResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetAvailableThirdPartyRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetAvailableThirdPartyRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetAvailableThirdPartyRequest, UAccountAvailableResponse>(
	const int64&, UGetAvailableThirdPartyRequest*, FOnGetAvailableThirdPartySuccess, FOnGetAvailableThirdPartyError, FOnGetAvailableThirdPartyComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetAvailableThirdPartyRequest, UAccountAvailableResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetAvailableThirdPartyRequest*, FOnGetAvailableThirdPartySuccess, FOnGetAvailableThirdPartyError, FOnGetAvailableThirdPartyComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetAvailableThirdPartyRequest*, TBeamFullResponseHandler<UGetAvailableThirdPartyRequest*, UAccountAvailableResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetAvailableThirdPartyRequest*,
                                                                                   TBeamFullResponseHandler<UGetAvailableThirdPartyRequest*, UAccountAvailableResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostPasswordUpdateInitRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostPasswordUpdateInitRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostPasswordUpdateInitRequest, UEmptyResponse>(
	const int64&, UPostPasswordUpdateInitRequest*, FOnPostPasswordUpdateInitSuccess, FOnPostPasswordUpdateInitError, FOnPostPasswordUpdateInitComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostPasswordUpdateInitRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostPasswordUpdateInitRequest*, FOnPostPasswordUpdateInitSuccess, FOnPostPasswordUpdateInitError, FOnPostPasswordUpdateInitComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostPasswordUpdateInitRequest*, TBeamFullResponseHandler<UPostPasswordUpdateInitRequest*, UEmptyResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostPasswordUpdateInitRequest*,
                                                                                   TBeamFullResponseHandler<UPostPasswordUpdateInitRequest*, UEmptyResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetAvailableDeviceIdRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetAvailableDeviceIdRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetAvailableDeviceIdRequest, UAccountAvailableResponse>(
	const int64&, UGetAvailableDeviceIdRequest*, FOnGetAvailableDeviceIdSuccess, FOnGetAvailableDeviceIdError, FOnGetAvailableDeviceIdComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetAvailableDeviceIdRequest, UAccountAvailableResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetAvailableDeviceIdRequest*, FOnGetAvailableDeviceIdSuccess, FOnGetAvailableDeviceIdError, FOnGetAvailableDeviceIdComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetAvailableDeviceIdRequest*, TBeamFullResponseHandler<UGetAvailableDeviceIdRequest*, UAccountAvailableResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetAvailableDeviceIdRequest*,
                                                                                   TBeamFullResponseHandler<UGetAvailableDeviceIdRequest*, UAccountAvailableResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetAvailableRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetAvailableRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetAvailableRequest, UAccountAvailableResponse>(
	const int64&, UGetAvailableRequest*, FOnGetAvailableSuccess, FOnGetAvailableError, FOnGetAvailableComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetAvailableRequest, UAccountAvailableResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetAvailableRequest*, FOnGetAvailableSuccess, FOnGetAvailableError, FOnGetAvailableComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetAvailableRequest*, TBeamFullResponseHandler<UGetAvailableRequest*, UAccountAvailableResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetAvailableRequest*,
                                                                                   TBeamFullResponseHandler<UGetAvailableRequest*, UAccountAvailableResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostPasswordUpdateConfirmRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostPasswordUpdateConfirmRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostPasswordUpdateConfirmRequest, UEmptyResponse>(
	const int64&, UPostPasswordUpdateConfirmRequest*, FOnPostPasswordUpdateConfirmSuccess, FOnPostPasswordUpdateConfirmError, FOnPostPasswordUpdateConfirmComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostPasswordUpdateConfirmRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostPasswordUpdateConfirmRequest*, FOnPostPasswordUpdateConfirmSuccess, FOnPostPasswordUpdateConfirmError, FOnPostPasswordUpdateConfirmComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostPasswordUpdateConfirmRequest*, TBeamFullResponseHandler<UPostPasswordUpdateConfirmRequest*, UEmptyResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostPasswordUpdateConfirmRequest*,
                                                                                   TBeamFullResponseHandler<UPostPasswordUpdateConfirmRequest*, UEmptyResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetAvailableRolesRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetAvailableRolesRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetAvailableRolesRequest, UAvailableRolesResponse>(
	const int64&, UGetAvailableRolesRequest*, FOnGetAvailableRolesSuccess, FOnGetAvailableRolesError, FOnGetAvailableRolesComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetAvailableRolesRequest, UAvailableRolesResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetAvailableRolesRequest*, FOnGetAvailableRolesSuccess, FOnGetAvailableRolesError, FOnGetAvailableRolesComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetAvailableRolesRequest*, TBeamFullResponseHandler<UGetAvailableRolesRequest*, UAvailableRolesResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetAvailableRolesRequest*,
                                                                                   TBeamFullResponseHandler<UGetAvailableRolesRequest*, UAvailableRolesResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UDeleteMeDeviceRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UDeleteMeDeviceRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UDeleteMeDeviceRequest, UAccountPlayerView>(
	const int64&, UDeleteMeDeviceRequest*, FOnDeleteMeDeviceSuccess, FOnDeleteMeDeviceError, FOnDeleteMeDeviceComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UDeleteMeDeviceRequest, UAccountPlayerView>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteMeDeviceRequest*, FOnDeleteMeDeviceSuccess, FOnDeleteMeDeviceError, FOnDeleteMeDeviceComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UDeleteMeDeviceRequest*, TBeamFullResponseHandler<UDeleteMeDeviceRequest*, UAccountPlayerView*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteMeDeviceRequest*,
                                                                                   TBeamFullResponseHandler<UDeleteMeDeviceRequest*, UAccountPlayerView*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UBasicAccountsGetMeRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UBasicAccountsGetMeRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UBasicAccountsGetMeRequest, UAccountPlayerView>(
	const int64&, UBasicAccountsGetMeRequest*, FOnBasicAccountsGetMeSuccess, FOnBasicAccountsGetMeError, FOnBasicAccountsGetMeComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UBasicAccountsGetMeRequest, UAccountPlayerView>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicAccountsGetMeRequest*, FOnBasicAccountsGetMeSuccess, FOnBasicAccountsGetMeError, FOnBasicAccountsGetMeComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UBasicAccountsGetMeRequest*, TBeamFullResponseHandler<UBasicAccountsGetMeRequest*, UAccountPlayerView*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicAccountsGetMeRequest*,
                                                                                   TBeamFullResponseHandler<UBasicAccountsGetMeRequest*, UAccountPlayerView*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutMeRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutMeRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutMeRequest, UAccountPlayerView>(
	const int64&, UPutMeRequest*, FOnPutMeSuccess, FOnPutMeError, FOnPutMeComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutMeRequest, UAccountPlayerView>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutMeRequest*, FOnPutMeSuccess, FOnPutMeError, FOnPutMeComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutMeRequest*, TBeamFullResponseHandler<UPutMeRequest*, UAccountPlayerView*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutMeRequest*,
                                                                                   TBeamFullResponseHandler<UPutMeRequest*, UAccountPlayerView*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UDeleteMeThirdPartyRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UDeleteMeThirdPartyRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UDeleteMeThirdPartyRequest, UAccountPlayerView>(
	const int64&, UDeleteMeThirdPartyRequest*, FOnDeleteMeThirdPartySuccess, FOnDeleteMeThirdPartyError, FOnDeleteMeThirdPartyComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UDeleteMeThirdPartyRequest, UAccountPlayerView>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteMeThirdPartyRequest*, FOnDeleteMeThirdPartySuccess, FOnDeleteMeThirdPartyError, FOnDeleteMeThirdPartyComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UDeleteMeThirdPartyRequest*, TBeamFullResponseHandler<UDeleteMeThirdPartyRequest*, UAccountPlayerView*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteMeThirdPartyRequest*,
                                                                                   TBeamFullResponseHandler<UDeleteMeThirdPartyRequest*, UAccountPlayerView*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UBasicAccountsGetSearchRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UBasicAccountsGetSearchRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UBasicAccountsGetSearchRequest, UAccountSearchResponse>(
	const int64&, UBasicAccountsGetSearchRequest*, FOnBasicAccountsGetSearchSuccess, FOnBasicAccountsGetSearchError, FOnBasicAccountsGetSearchComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UBasicAccountsGetSearchRequest, UAccountSearchResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicAccountsGetSearchRequest*, FOnBasicAccountsGetSearchSuccess, FOnBasicAccountsGetSearchError, FOnBasicAccountsGetSearchComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UBasicAccountsGetSearchRequest*, TBeamFullResponseHandler<UBasicAccountsGetSearchRequest*, UAccountSearchResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicAccountsGetSearchRequest*,
                                                                                   TBeamFullResponseHandler<UBasicAccountsGetSearchRequest*, UAccountSearchResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostEmailUpdateInitRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostEmailUpdateInitRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostEmailUpdateInitRequest, UEmptyResponse>(
	const int64&, UPostEmailUpdateInitRequest*, FOnPostEmailUpdateInitSuccess, FOnPostEmailUpdateInitError, FOnPostEmailUpdateInitComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostEmailUpdateInitRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostEmailUpdateInitRequest*, FOnPostEmailUpdateInitSuccess, FOnPostEmailUpdateInitError, FOnPostEmailUpdateInitComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostEmailUpdateInitRequest*, TBeamFullResponseHandler<UPostEmailUpdateInitRequest*, UEmptyResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostEmailUpdateInitRequest*,
                                                                                   TBeamFullResponseHandler<UPostEmailUpdateInitRequest*, UEmptyResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostEmailUpdateConfirmRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostEmailUpdateConfirmRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostEmailUpdateConfirmRequest, UEmptyResponse>(
	const int64&, UPostEmailUpdateConfirmRequest*, FOnPostEmailUpdateConfirmSuccess, FOnPostEmailUpdateConfirmError, FOnPostEmailUpdateConfirmComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostEmailUpdateConfirmRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostEmailUpdateConfirmRequest*, FOnPostEmailUpdateConfirmSuccess, FOnPostEmailUpdateConfirmError, FOnPostEmailUpdateConfirmComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostEmailUpdateConfirmRequest*, TBeamFullResponseHandler<UPostEmailUpdateConfirmRequest*, UEmptyResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostEmailUpdateConfirmRequest*,
                                                                                   TBeamFullResponseHandler<UPostEmailUpdateConfirmRequest*, UEmptyResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostAdminAdminUserRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostAdminAdminUserRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostAdminAdminUserRequest, UAccountPortalView>(
	const int64&, UPostAdminAdminUserRequest*, FOnPostAdminAdminUserSuccess, FOnPostAdminAdminUserError, FOnPostAdminAdminUserComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostAdminAdminUserRequest, UAccountPortalView>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostAdminAdminUserRequest*, FOnPostAdminAdminUserSuccess, FOnPostAdminAdminUserError, FOnPostAdminAdminUserComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostAdminAdminUserRequest*, TBeamFullResponseHandler<UPostAdminAdminUserRequest*, UAccountPortalView*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostAdminAdminUserRequest*,
                                                                                   TBeamFullResponseHandler<UPostAdminAdminUserRequest*, UAccountPortalView*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UBasicAccountsPostRegisterRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UBasicAccountsPostRegisterRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UBasicAccountsPostRegisterRequest, UAccountPlayerView>(
	const int64&, UBasicAccountsPostRegisterRequest*, FOnBasicAccountsPostRegisterSuccess, FOnBasicAccountsPostRegisterError, FOnBasicAccountsPostRegisterComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UBasicAccountsPostRegisterRequest, UAccountPlayerView>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicAccountsPostRegisterRequest*, FOnBasicAccountsPostRegisterSuccess, FOnBasicAccountsPostRegisterError, FOnBasicAccountsPostRegisterComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UBasicAccountsPostRegisterRequest*, TBeamFullResponseHandler<UBasicAccountsPostRegisterRequest*, UAccountPlayerView*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicAccountsPostRegisterRequest*,
                                                                                   TBeamFullResponseHandler<UBasicAccountsPostRegisterRequest*, UAccountPlayerView*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetAdminMeRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetAdminMeRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetAdminMeRequest, UAccountPortalView>(
	const int64&, UGetAdminMeRequest*, FOnGetAdminMeSuccess, FOnGetAdminMeError, FOnGetAdminMeComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetAdminMeRequest, UAccountPortalView>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetAdminMeRequest*, FOnGetAdminMeSuccess, FOnGetAdminMeError, FOnGetAdminMeComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetAdminMeRequest*, TBeamFullResponseHandler<UGetAdminMeRequest*, UAccountPortalView*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetAdminMeRequest*,
                                                                                   TBeamFullResponseHandler<UGetAdminMeRequest*, UAccountPortalView*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetAdminAdminUsersRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetAdminAdminUsersRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetAdminAdminUsersRequest, UGetAdminsResponse>(
	const int64&, UGetAdminAdminUsersRequest*, FOnGetAdminAdminUsersSuccess, FOnGetAdminAdminUsersError, FOnGetAdminAdminUsersComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetAdminAdminUsersRequest, UGetAdminsResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetAdminAdminUsersRequest*, FOnGetAdminAdminUsersSuccess, FOnGetAdminAdminUsersError, FOnGetAdminAdminUsersComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetAdminAdminUsersRequest*, TBeamFullResponseHandler<UGetAdminAdminUsersRequest*, UGetAdminsResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetAdminAdminUsersRequest*,
                                                                                   TBeamFullResponseHandler<UGetAdminAdminUsersRequest*, UGetAdminsResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetFindRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetFindRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetFindRequest, UAccountsBasicAccount>(
	const int64&, UGetFindRequest*, FOnGetFindSuccess, FOnGetFindError, FOnGetFindComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetFindRequest, UAccountsBasicAccount>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetFindRequest*, FOnGetFindSuccess, FOnGetFindError, FOnGetFindComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetFindRequest*, TBeamFullResponseHandler<UGetFindRequest*, UAccountsBasicAccount*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetFindRequest*,
                                                                                   TBeamFullResponseHandler<UGetFindRequest*, UAccountsBasicAccount*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostExternal_identityRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostExternal_identityRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostExternal_identityRequest, UAttachExternalIdentityApiResponse>(
	const int64&, UPostExternal_identityRequest*, FOnPostExternal_identitySuccess, FOnPostExternal_identityError, FOnPostExternal_identityComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostExternal_identityRequest, UAttachExternalIdentityApiResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostExternal_identityRequest*, FOnPostExternal_identitySuccess, FOnPostExternal_identityError, FOnPostExternal_identityComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostExternal_identityRequest*, TBeamFullResponseHandler<UPostExternal_identityRequest*, UAttachExternalIdentityApiResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostExternal_identityRequest*,
                                                                                   TBeamFullResponseHandler<UPostExternal_identityRequest*, UAttachExternalIdentityApiResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UDeleteExternal_identityRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UDeleteExternal_identityRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UDeleteExternal_identityRequest, UCommonResponse>(
	const int64&, UDeleteExternal_identityRequest*, FOnDeleteExternal_identitySuccess, FOnDeleteExternal_identityError, FOnDeleteExternal_identityComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UDeleteExternal_identityRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteExternal_identityRequest*, FOnDeleteExternal_identitySuccess, FOnDeleteExternal_identityError, FOnDeleteExternal_identityComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UDeleteExternal_identityRequest*, TBeamFullResponseHandler<UDeleteExternal_identityRequest*, UCommonResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteExternal_identityRequest*,
                                                                                   TBeamFullResponseHandler<UDeleteExternal_identityRequest*, UCommonResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutAdminEmailRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutAdminEmailRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutAdminEmailRequest, UAccountsObjectAccount>(
	const int64&, UPutAdminEmailRequest*, FOnPutAdminEmailSuccess, FOnPutAdminEmailError, FOnPutAdminEmailComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutAdminEmailRequest, UAccountsObjectAccount>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutAdminEmailRequest*, FOnPutAdminEmailSuccess, FOnPutAdminEmailError, FOnPutAdminEmailComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutAdminEmailRequest*, TBeamFullResponseHandler<UPutAdminEmailRequest*, UAccountsObjectAccount*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutAdminEmailRequest*,
                                                                                   TBeamFullResponseHandler<UPutAdminEmailRequest*, UAccountsObjectAccount*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetRoleReportRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetRoleReportRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetRoleReportRequest, UAccountRolesReport>(
	const int64&, UGetRoleReportRequest*, FOnGetRoleReportSuccess, FOnGetRoleReportError, FOnGetRoleReportComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetRoleReportRequest, UAccountRolesReport>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetRoleReportRequest*, FOnGetRoleReportSuccess, FOnGetRoleReportError, FOnGetRoleReportComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetRoleReportRequest*, TBeamFullResponseHandler<UGetRoleReportRequest*, UAccountRolesReport*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetRoleReportRequest*,
                                                                                   TBeamFullResponseHandler<UGetRoleReportRequest*, UAccountRolesReport*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UObjectAccountsPutRoleRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UObjectAccountsPutRoleRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UObjectAccountsPutRoleRequest, UEmptyResponse>(
	const int64&, UObjectAccountsPutRoleRequest*, FOnObjectAccountsPutRoleSuccess, FOnObjectAccountsPutRoleError, FOnObjectAccountsPutRoleComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UObjectAccountsPutRoleRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UObjectAccountsPutRoleRequest*, FOnObjectAccountsPutRoleSuccess, FOnObjectAccountsPutRoleError, FOnObjectAccountsPutRoleComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UObjectAccountsPutRoleRequest*, TBeamFullResponseHandler<UObjectAccountsPutRoleRequest*, UEmptyResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UObjectAccountsPutRoleRequest*,
                                                                                   TBeamFullResponseHandler<UObjectAccountsPutRoleRequest*, UEmptyResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UDeleteRoleRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UDeleteRoleRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UDeleteRoleRequest, UEmptyResponse>(
	const int64&, UDeleteRoleRequest*, FOnDeleteRoleSuccess, FOnDeleteRoleError, FOnDeleteRoleComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UDeleteRoleRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteRoleRequest*, FOnDeleteRoleSuccess, FOnDeleteRoleError, FOnDeleteRoleComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UDeleteRoleRequest*, TBeamFullResponseHandler<UDeleteRoleRequest*, UEmptyResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteRoleRequest*,
                                                                                   TBeamFullResponseHandler<UDeleteRoleRequest*, UEmptyResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutAdminScopeRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutAdminScopeRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutAdminScopeRequest, UEmptyResponse>(
	const int64&, UPutAdminScopeRequest*, FOnPutAdminScopeSuccess, FOnPutAdminScopeError, FOnPutAdminScopeComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutAdminScopeRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutAdminScopeRequest*, FOnPutAdminScopeSuccess, FOnPutAdminScopeError, FOnPutAdminScopeComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutAdminScopeRequest*, TBeamFullResponseHandler<UPutAdminScopeRequest*, UEmptyResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutAdminScopeRequest*,
                                                                                   TBeamFullResponseHandler<UPutAdminScopeRequest*, UEmptyResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UDeleteAdminScopeRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UDeleteAdminScopeRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UDeleteAdminScopeRequest, UEmptyResponse>(
	const int64&, UDeleteAdminScopeRequest*, FOnDeleteAdminScopeSuccess, FOnDeleteAdminScopeError, FOnDeleteAdminScopeComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UDeleteAdminScopeRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteAdminScopeRequest*, FOnDeleteAdminScopeSuccess, FOnDeleteAdminScopeError, FOnDeleteAdminScopeComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UDeleteAdminScopeRequest*, TBeamFullResponseHandler<UDeleteAdminScopeRequest*, UEmptyResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteAdminScopeRequest*,
                                                                                   TBeamFullResponseHandler<UDeleteAdminScopeRequest*, UEmptyResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutAdminThirdPartyRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutAdminThirdPartyRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutAdminThirdPartyRequest, UEmptyResponse>(
	const int64&, UPutAdminThirdPartyRequest*, FOnPutAdminThirdPartySuccess, FOnPutAdminThirdPartyError, FOnPutAdminThirdPartyComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutAdminThirdPartyRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutAdminThirdPartyRequest*, FOnPutAdminThirdPartySuccess, FOnPutAdminThirdPartyError, FOnPutAdminThirdPartyComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutAdminThirdPartyRequest*, TBeamFullResponseHandler<UPutAdminThirdPartyRequest*, UEmptyResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutAdminThirdPartyRequest*,
                                                                                   TBeamFullResponseHandler<UPutAdminThirdPartyRequest*, UEmptyResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UDeleteAdminThirdPartyRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UDeleteAdminThirdPartyRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UDeleteAdminThirdPartyRequest, UEmptyResponse>(
	const int64&, UDeleteAdminThirdPartyRequest*, FOnDeleteAdminThirdPartySuccess, FOnDeleteAdminThirdPartyError, FOnDeleteAdminThirdPartyComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UDeleteAdminThirdPartyRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteAdminThirdPartyRequest*, FOnDeleteAdminThirdPartySuccess, FOnDeleteAdminThirdPartyError, FOnDeleteAdminThirdPartyComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UDeleteAdminThirdPartyRequest*, TBeamFullResponseHandler<UDeleteAdminThirdPartyRequest*, UEmptyResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteAdminThirdPartyRequest*,
                                                                                   TBeamFullResponseHandler<UDeleteAdminThirdPartyRequest*, UEmptyResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutAccountsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutAccountsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutAccountsRequest, UAccountsObjectAccount>(
	const int64&, UPutAccountsRequest*, FOnPutAccountsSuccess, FOnPutAccountsError, FOnPutAccountsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutAccountsRequest, UAccountsObjectAccount>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutAccountsRequest*, FOnPutAccountsSuccess, FOnPutAccountsError, FOnPutAccountsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutAccountsRequest*, TBeamFullResponseHandler<UPutAccountsRequest*, UAccountsObjectAccount*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutAccountsRequest*,
                                                                                   TBeamFullResponseHandler<UPutAccountsRequest*, UAccountsObjectAccount*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UDeleteAdminForgetRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UDeleteAdminForgetRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UDeleteAdminForgetRequest, UAccountsObjectAccount>(
	const int64&, UDeleteAdminForgetRequest*, FOnDeleteAdminForgetSuccess, FOnDeleteAdminForgetError, FOnDeleteAdminForgetComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UDeleteAdminForgetRequest, UAccountsObjectAccount>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteAdminForgetRequest*, FOnDeleteAdminForgetSuccess, FOnDeleteAdminForgetError, FOnDeleteAdminForgetComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UDeleteAdminForgetRequest*, TBeamFullResponseHandler<UDeleteAdminForgetRequest*, UAccountsObjectAccount*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteAdminForgetRequest*,
                                                                                   TBeamFullResponseHandler<UDeleteAdminForgetRequest*, UAccountsObjectAccount*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetClientBatchRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetClientBatchRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetClientBatchRequest, UBatchReadStatsResponse>(
	const int64&, UGetClientBatchRequest*, FOnGetClientBatchSuccess, FOnGetClientBatchError, FOnGetClientBatchComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetClientBatchRequest, UBatchReadStatsResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetClientBatchRequest*, FOnGetClientBatchSuccess, FOnGetClientBatchError, FOnGetClientBatchComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetClientBatchRequest*, TBeamFullResponseHandler<UGetClientBatchRequest*, UBatchReadStatsResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetClientBatchRequest*,
                                                                                   TBeamFullResponseHandler<UGetClientBatchRequest*, UBatchReadStatsResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostClientStringlistRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostClientStringlistRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostClientStringlistRequest, UEmptyResponse>(
	const int64&, UPostClientStringlistRequest*, FOnPostClientStringlistSuccess, FOnPostClientStringlistError, FOnPostClientStringlistComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostClientStringlistRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostClientStringlistRequest*, FOnPostClientStringlistSuccess, FOnPostClientStringlistError, FOnPostClientStringlistComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostClientStringlistRequest*, TBeamFullResponseHandler<UPostClientStringlistRequest*, UEmptyResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostClientStringlistRequest*,
                                                                                   TBeamFullResponseHandler<UPostClientStringlistRequest*, UEmptyResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetClientRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetClientRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetClientRequest, UStatsResponse>(
	const int64&, UGetClientRequest*, FOnGetClientSuccess, FOnGetClientError, FOnGetClientComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetClientRequest, UStatsResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetClientRequest*, FOnGetClientSuccess, FOnGetClientError, FOnGetClientComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetClientRequest*, TBeamFullResponseHandler<UGetClientRequest*, UStatsResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetClientRequest*,
                                                                                   TBeamFullResponseHandler<UGetClientRequest*, UStatsResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostClientRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostClientRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostClientRequest, UEmptyResponse>(
	const int64&, UPostClientRequest*, FOnPostClientSuccess, FOnPostClientError, FOnPostClientComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostClientRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostClientRequest*, FOnPostClientSuccess, FOnPostClientError, FOnPostClientComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostClientRequest*, TBeamFullResponseHandler<UPostClientRequest*, UEmptyResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostClientRequest*,
                                                                                   TBeamFullResponseHandler<UPostClientRequest*, UEmptyResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutSubscribeRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutSubscribeRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutSubscribeRequest, UCommonResponse>(
	const int64&, UPutSubscribeRequest*, FOnPutSubscribeSuccess, FOnPutSubscribeError, FOnPutSubscribeComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutSubscribeRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutSubscribeRequest*, FOnPutSubscribeSuccess, FOnPutSubscribeError, FOnPutSubscribeComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutSubscribeRequest*, TBeamFullResponseHandler<UPutSubscribeRequest*, UCommonResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutSubscribeRequest*,
                                                                                   TBeamFullResponseHandler<UPutSubscribeRequest*, UCommonResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostBatchRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostBatchRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostBatchRequest, UEmptyResponse>(
	const int64&, UPostBatchRequest*, FOnPostBatchSuccess, FOnPostBatchError, FOnPostBatchComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostBatchRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostBatchRequest*, FOnPostBatchSuccess, FOnPostBatchError, FOnPostBatchComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostBatchRequest*, TBeamFullResponseHandler<UPostBatchRequest*, UEmptyResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostBatchRequest*,
                                                                                   TBeamFullResponseHandler<UPostBatchRequest*, UEmptyResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UBasicStatsPostSearchRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UBasicStatsPostSearchRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UBasicStatsPostSearchRequest, UStatsSearchResponse>(
	const int64&, UBasicStatsPostSearchRequest*, FOnBasicStatsPostSearchSuccess, FOnBasicStatsPostSearchError, FOnBasicStatsPostSearchComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UBasicStatsPostSearchRequest, UStatsSearchResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicStatsPostSearchRequest*, FOnBasicStatsPostSearchSuccess, FOnBasicStatsPostSearchError, FOnBasicStatsPostSearchComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UBasicStatsPostSearchRequest*, TBeamFullResponseHandler<UBasicStatsPostSearchRequest*, UStatsSearchResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicStatsPostSearchRequest*,
                                                                                   TBeamFullResponseHandler<UBasicStatsPostSearchRequest*, UStatsSearchResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostSearchExtendedRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostSearchExtendedRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostSearchExtendedRequest, USearchExtendedResponse>(
	const int64&, UPostSearchExtendedRequest*, FOnPostSearchExtendedSuccess, FOnPostSearchExtendedError, FOnPostSearchExtendedComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostSearchExtendedRequest, USearchExtendedResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostSearchExtendedRequest*, FOnPostSearchExtendedSuccess, FOnPostSearchExtendedError, FOnPostSearchExtendedComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostSearchExtendedRequest*, TBeamFullResponseHandler<UPostSearchExtendedRequest*, USearchExtendedResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostSearchExtendedRequest*,
                                                                                   TBeamFullResponseHandler<UPostSearchExtendedRequest*, USearchExtendedResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetStatsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetStatsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetStatsRequest, UStatsResponse>(
	const int64&, UGetStatsRequest*, FOnGetStatsSuccess, FOnGetStatsError, FOnGetStatsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetStatsRequest, UStatsResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetStatsRequest*, FOnGetStatsSuccess, FOnGetStatsError, FOnGetStatsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetStatsRequest*, TBeamFullResponseHandler<UGetStatsRequest*, UStatsResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetStatsRequest*,
                                                                                   TBeamFullResponseHandler<UGetStatsRequest*, UStatsResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostStatsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostStatsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostStatsRequest, UEmptyResponse>(
	const int64&, UPostStatsRequest*, FOnPostStatsSuccess, FOnPostStatsError, FOnPostStatsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostStatsRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostStatsRequest*, FOnPostStatsSuccess, FOnPostStatsError, FOnPostStatsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostStatsRequest*, TBeamFullResponseHandler<UPostStatsRequest*, UEmptyResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostStatsRequest*,
                                                                                   TBeamFullResponseHandler<UPostStatsRequest*, UEmptyResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UDeleteStatsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UDeleteStatsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UDeleteStatsRequest, UEmptyResponse>(
	const int64&, UDeleteStatsRequest*, FOnDeleteStatsSuccess, FOnDeleteStatsError, FOnDeleteStatsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UDeleteStatsRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteStatsRequest*, FOnDeleteStatsSuccess, FOnDeleteStatsError, FOnDeleteStatsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UDeleteStatsRequest*, TBeamFullResponseHandler<UDeleteStatsRequest*, UEmptyResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteStatsRequest*,
                                                                                   TBeamFullResponseHandler<UDeleteStatsRequest*, UEmptyResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostSearchGroupsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostSearchGroupsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostSearchGroupsRequest, UGetStatusForGroupsResponse>(
	const int64&, UPostSearchGroupsRequest*, FOnPostSearchGroupsSuccess, FOnPostSearchGroupsError, FOnPostSearchGroupsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostSearchGroupsRequest, UGetStatusForGroupsResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostSearchGroupsRequest*, FOnPostSearchGroupsSuccess, FOnPostSearchGroupsError, FOnPostSearchGroupsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostSearchGroupsRequest*, TBeamFullResponseHandler<UPostSearchGroupsRequest*, UGetStatusForGroupsResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostSearchGroupsRequest*,
                                                                                   TBeamFullResponseHandler<UPostSearchGroupsRequest*, UGetStatusForGroupsResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UBasicTournamentsGetTournamentsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UBasicTournamentsGetTournamentsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UBasicTournamentsGetTournamentsRequest, UTournamentQueryResponse>(
	const int64&, UBasicTournamentsGetTournamentsRequest*, FOnBasicTournamentsGetTournamentsSuccess, FOnBasicTournamentsGetTournamentsError, FOnBasicTournamentsGetTournamentsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UBasicTournamentsGetTournamentsRequest, UTournamentQueryResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicTournamentsGetTournamentsRequest*, FOnBasicTournamentsGetTournamentsSuccess, FOnBasicTournamentsGetTournamentsError, FOnBasicTournamentsGetTournamentsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UBasicTournamentsGetTournamentsRequest*, TBeamFullResponseHandler<UBasicTournamentsGetTournamentsRequest*, UTournamentQueryResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicTournamentsGetTournamentsRequest*,
                                                                                   TBeamFullResponseHandler<UBasicTournamentsGetTournamentsRequest*, UTournamentQueryResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostScoreRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostScoreRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostScoreRequest, UEmptyResponse>(
	const int64&, UPostScoreRequest*, FOnPostScoreSuccess, FOnPostScoreError, FOnPostScoreComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostScoreRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostScoreRequest*, FOnPostScoreSuccess, FOnPostScoreError, FOnPostScoreComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostScoreRequest*, TBeamFullResponseHandler<UPostScoreRequest*, UEmptyResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostScoreRequest*,
                                                                                   TBeamFullResponseHandler<UPostScoreRequest*, UEmptyResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UObjectTournamentsGetTournamentsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UObjectTournamentsGetTournamentsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UObjectTournamentsGetTournamentsRequest, UTournamentClientView>(
	const int64&, UObjectTournamentsGetTournamentsRequest*, FOnObjectTournamentsGetTournamentsSuccess, FOnObjectTournamentsGetTournamentsError, FOnObjectTournamentsGetTournamentsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UObjectTournamentsGetTournamentsRequest, UTournamentClientView>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UObjectTournamentsGetTournamentsRequest*, FOnObjectTournamentsGetTournamentsSuccess, FOnObjectTournamentsGetTournamentsError, FOnObjectTournamentsGetTournamentsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UObjectTournamentsGetTournamentsRequest*, TBeamFullResponseHandler<UObjectTournamentsGetTournamentsRequest*, UTournamentClientView*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UObjectTournamentsGetTournamentsRequest*,
                                                                                   TBeamFullResponseHandler<UObjectTournamentsGetTournamentsRequest*, UTournamentClientView*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostTournamentsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostTournamentsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostTournamentsRequest, UPlayerStatus>(
	const int64&, UPostTournamentsRequest*, FOnPostTournamentsSuccess, FOnPostTournamentsError, FOnPostTournamentsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostTournamentsRequest, UPlayerStatus>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostTournamentsRequest*, FOnPostTournamentsSuccess, FOnPostTournamentsError, FOnPostTournamentsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostTournamentsRequest*, TBeamFullResponseHandler<UPostTournamentsRequest*, UPlayerStatus*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostTournamentsRequest*,
                                                                                   TBeamFullResponseHandler<UPostTournamentsRequest*, UPlayerStatus*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetMeGroupRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetMeGroupRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetMeGroupRequest, UGetGroupStatusResponse>(
	const int64&, UGetMeGroupRequest*, FOnGetMeGroupSuccess, FOnGetMeGroupError, FOnGetMeGroupComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetMeGroupRequest, UGetGroupStatusResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetMeGroupRequest*, FOnGetMeGroupSuccess, FOnGetMeGroupError, FOnGetMeGroupComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetMeGroupRequest*, TBeamFullResponseHandler<UGetMeGroupRequest*, UGetGroupStatusResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetMeGroupRequest*,
                                                                                   TBeamFullResponseHandler<UGetMeGroupRequest*, UGetGroupStatusResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetRewardsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetRewardsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetRewardsRequest, URewardsResponse>(
	const int64&, UGetRewardsRequest*, FOnGetRewardsSuccess, FOnGetRewardsError, FOnGetRewardsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetRewardsRequest, URewardsResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetRewardsRequest*, FOnGetRewardsSuccess, FOnGetRewardsError, FOnGetRewardsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetRewardsRequest*, TBeamFullResponseHandler<UGetRewardsRequest*, URewardsResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetRewardsRequest*,
                                                                                   TBeamFullResponseHandler<UGetRewardsRequest*, URewardsResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostRewardsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostRewardsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostRewardsRequest, URewardsResponse>(
	const int64&, UPostRewardsRequest*, FOnPostRewardsSuccess, FOnPostRewardsError, FOnPostRewardsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostRewardsRequest, URewardsResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostRewardsRequest*, FOnPostRewardsSuccess, FOnPostRewardsError, FOnPostRewardsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostRewardsRequest*, TBeamFullResponseHandler<UPostRewardsRequest*, URewardsResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostRewardsRequest*,
                                                                                   TBeamFullResponseHandler<UPostRewardsRequest*, URewardsResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetGlobalRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetGlobalRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetGlobalRequest, UGetStandingsResponse>(
	const int64&, UGetGlobalRequest*, FOnGetGlobalSuccess, FOnGetGlobalError, FOnGetGlobalComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetGlobalRequest, UGetStandingsResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetGlobalRequest*, FOnGetGlobalSuccess, FOnGetGlobalError, FOnGetGlobalComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetGlobalRequest*, TBeamFullResponseHandler<UGetGlobalRequest*, UGetStandingsResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetGlobalRequest*,
                                                                                   TBeamFullResponseHandler<UGetGlobalRequest*, UGetStandingsResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetStandingsGroupRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetStandingsGroupRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetStandingsGroupRequest, UGetStandingsResponse>(
	const int64&, UGetStandingsGroupRequest*, FOnGetStandingsGroupSuccess, FOnGetStandingsGroupError, FOnGetStandingsGroupComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetStandingsGroupRequest, UGetStandingsResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetStandingsGroupRequest*, FOnGetStandingsGroupSuccess, FOnGetStandingsGroupError, FOnGetStandingsGroupComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetStandingsGroupRequest*, TBeamFullResponseHandler<UGetStandingsGroupRequest*, UGetStandingsResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetStandingsGroupRequest*,
                                                                                   TBeamFullResponseHandler<UGetStandingsGroupRequest*, UGetStandingsResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetStandingsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetStandingsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetStandingsRequest, UGetStandingsResponse>(
	const int64&, UGetStandingsRequest*, FOnGetStandingsSuccess, FOnGetStandingsError, FOnGetStandingsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetStandingsRequest, UGetStandingsResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetStandingsRequest*, FOnGetStandingsSuccess, FOnGetStandingsError, FOnGetStandingsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetStandingsRequest*, TBeamFullResponseHandler<UGetStandingsRequest*, UGetStandingsResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetStandingsRequest*,
                                                                                   TBeamFullResponseHandler<UGetStandingsRequest*, UGetStandingsResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetAdminPlayerRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetAdminPlayerRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetAdminPlayerRequest, UAdminGetPlayerStatusResponse>(
	const int64&, UGetAdminPlayerRequest*, FOnGetAdminPlayerSuccess, FOnGetAdminPlayerError, FOnGetAdminPlayerComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetAdminPlayerRequest, UAdminGetPlayerStatusResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetAdminPlayerRequest*, FOnGetAdminPlayerSuccess, FOnGetAdminPlayerError, FOnGetAdminPlayerComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetAdminPlayerRequest*, TBeamFullResponseHandler<UGetAdminPlayerRequest*, UAdminGetPlayerStatusResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetAdminPlayerRequest*,
                                                                                   TBeamFullResponseHandler<UGetAdminPlayerRequest*, UAdminGetPlayerStatusResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutAdminPlayerRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutAdminPlayerRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutAdminPlayerRequest, UAdminPlayerStatus>(
	const int64&, UPutAdminPlayerRequest*, FOnPutAdminPlayerSuccess, FOnPutAdminPlayerError, FOnPutAdminPlayerComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutAdminPlayerRequest, UAdminPlayerStatus>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutAdminPlayerRequest*, FOnPutAdminPlayerSuccess, FOnPutAdminPlayerError, FOnPutAdminPlayerComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutAdminPlayerRequest*, TBeamFullResponseHandler<UPutAdminPlayerRequest*, UAdminPlayerStatus*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutAdminPlayerRequest*,
                                                                                   TBeamFullResponseHandler<UPutAdminPlayerRequest*, UAdminPlayerStatus*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UBasicTournamentsGetMeRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UBasicTournamentsGetMeRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UBasicTournamentsGetMeRequest, UGetPlayerStatusResponse>(
	const int64&, UBasicTournamentsGetMeRequest*, FOnBasicTournamentsGetMeSuccess, FOnBasicTournamentsGetMeError, FOnBasicTournamentsGetMeComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UBasicTournamentsGetMeRequest, UGetPlayerStatusResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicTournamentsGetMeRequest*, FOnBasicTournamentsGetMeSuccess, FOnBasicTournamentsGetMeError, FOnBasicTournamentsGetMeComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UBasicTournamentsGetMeRequest*, TBeamFullResponseHandler<UBasicTournamentsGetMeRequest*, UGetPlayerStatusResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicTournamentsGetMeRequest*,
                                                                                   TBeamFullResponseHandler<UBasicTournamentsGetMeRequest*, UGetPlayerStatusResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetChampionsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetChampionsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetChampionsRequest, UGetChampionsResponse>(
	const int64&, UGetChampionsRequest*, FOnGetChampionsSuccess, FOnGetChampionsError, FOnGetChampionsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetChampionsRequest, UGetChampionsResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetChampionsRequest*, FOnGetChampionsSuccess, FOnGetChampionsError, FOnGetChampionsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetChampionsRequest*, TBeamFullResponseHandler<UGetChampionsRequest*, UGetChampionsResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetChampionsRequest*,
                                                                                   TBeamFullResponseHandler<UGetChampionsRequest*, UGetChampionsResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UBasicTournamentsGetGroupsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UBasicTournamentsGetGroupsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UBasicTournamentsGetGroupsRequest, UGetGroupsResponse>(
	const int64&, UBasicTournamentsGetGroupsRequest*, FOnBasicTournamentsGetGroupsSuccess, FOnBasicTournamentsGetGroupsError, FOnBasicTournamentsGetGroupsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UBasicTournamentsGetGroupsRequest, UGetGroupsResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicTournamentsGetGroupsRequest*, FOnBasicTournamentsGetGroupsSuccess, FOnBasicTournamentsGetGroupsError, FOnBasicTournamentsGetGroupsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UBasicTournamentsGetGroupsRequest*, TBeamFullResponseHandler<UBasicTournamentsGetGroupsRequest*, UGetGroupsResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicTournamentsGetGroupsRequest*,
                                                                                   TBeamFullResponseHandler<UBasicTournamentsGetGroupsRequest*, UGetGroupsResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetTokenRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetTokenRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetTokenRequest, UToken>(
	const int64&, UGetTokenRequest*, FOnGetTokenSuccess, FOnGetTokenError, FOnGetTokenComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetTokenRequest, UToken>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetTokenRequest*, FOnGetTokenSuccess, FOnGetTokenError, FOnGetTokenComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetTokenRequest*, TBeamFullResponseHandler<UGetTokenRequest*, UToken*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetTokenRequest*,
                                                                                   TBeamFullResponseHandler<UGetTokenRequest*, UToken*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UAuthenticateRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UAuthenticateRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UAuthenticateRequest, UTokenResponse>(
	const int64&, UAuthenticateRequest*, FOnAuthenticateSuccess, FOnAuthenticateError, FOnAuthenticateComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UAuthenticateRequest, UTokenResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UAuthenticateRequest*, FOnAuthenticateSuccess, FOnAuthenticateError, FOnAuthenticateComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UAuthenticateRequest*, TBeamFullResponseHandler<UAuthenticateRequest*, UTokenResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UAuthenticateRequest*,
                                                                                   TBeamFullResponseHandler<UAuthenticateRequest*, UTokenResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetTokenListRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetTokenListRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetTokenListRequest, UListTokenResponse>(
	const int64&, UGetTokenListRequest*, FOnGetTokenListSuccess, FOnGetTokenListError, FOnGetTokenListComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetTokenListRequest, UListTokenResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetTokenListRequest*, FOnGetTokenListSuccess, FOnGetTokenListError, FOnGetTokenListComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetTokenListRequest*, TBeamFullResponseHandler<UGetTokenListRequest*, UListTokenResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetTokenListRequest*,
                                                                                   TBeamFullResponseHandler<UGetTokenListRequest*, UListTokenResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutTokenRevokeRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutTokenRevokeRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutTokenRevokeRequest, UCommonResponse>(
	const int64&, UPutTokenRevokeRequest*, FOnPutTokenRevokeSuccess, FOnPutTokenRevokeError, FOnPutTokenRevokeComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutTokenRevokeRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutTokenRevokeRequest*, FOnPutTokenRevokeSuccess, FOnPutTokenRevokeError, FOnPutTokenRevokeComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutTokenRevokeRequest*, TBeamFullResponseHandler<UPutTokenRevokeRequest*, UCommonResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutTokenRevokeRequest*,
                                                                                   TBeamFullResponseHandler<UPutTokenRevokeRequest*, UCommonResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetCloudsavingRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetCloudsavingRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetCloudsavingRequest, UCloudsavingBasicManifest>(
	const int64&, UGetCloudsavingRequest*, FOnGetCloudsavingSuccess, FOnGetCloudsavingError, FOnGetCloudsavingComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetCloudsavingRequest, UCloudsavingBasicManifest>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetCloudsavingRequest*, FOnGetCloudsavingSuccess, FOnGetCloudsavingError, FOnGetCloudsavingComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetCloudsavingRequest*, TBeamFullResponseHandler<UGetCloudsavingRequest*, UCloudsavingBasicManifest*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetCloudsavingRequest*,
                                                                                   TBeamFullResponseHandler<UGetCloudsavingRequest*, UCloudsavingBasicManifest*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostDataReplaceRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostDataReplaceRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostDataReplaceRequest, UCloudsavingBasicManifest>(
	const int64&, UPostDataReplaceRequest*, FOnPostDataReplaceSuccess, FOnPostDataReplaceError, FOnPostDataReplaceComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostDataReplaceRequest, UCloudsavingBasicManifest>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostDataReplaceRequest*, FOnPostDataReplaceSuccess, FOnPostDataReplaceError, FOnPostDataReplaceComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostDataReplaceRequest*, TBeamFullResponseHandler<UPostDataReplaceRequest*, UCloudsavingBasicManifest*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostDataReplaceRequest*,
                                                                                   TBeamFullResponseHandler<UPostDataReplaceRequest*, UCloudsavingBasicManifest*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UDeleteDataRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UDeleteDataRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UDeleteDataRequest, UEmptyResponse>(
	const int64&, UDeleteDataRequest*, FOnDeleteDataSuccess, FOnDeleteDataError, FOnDeleteDataComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UDeleteDataRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteDataRequest*, FOnDeleteDataSuccess, FOnDeleteDataError, FOnDeleteDataComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UDeleteDataRequest*, TBeamFullResponseHandler<UDeleteDataRequest*, UEmptyResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteDataRequest*,
                                                                                   TBeamFullResponseHandler<UDeleteDataRequest*, UEmptyResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostDataDownloadURLRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostDataDownloadURLRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostDataDownloadURLRequest, UURLSResponse>(
	const int64&, UPostDataDownloadURLRequest*, FOnPostDataDownloadURLSuccess, FOnPostDataDownloadURLError, FOnPostDataDownloadURLComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostDataDownloadURLRequest, UURLSResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostDataDownloadURLRequest*, FOnPostDataDownloadURLSuccess, FOnPostDataDownloadURLError, FOnPostDataDownloadURLComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostDataDownloadURLRequest*, TBeamFullResponseHandler<UPostDataDownloadURLRequest*, UURLSResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostDataDownloadURLRequest*,
                                                                                   TBeamFullResponseHandler<UPostDataDownloadURLRequest*, UURLSResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetDataMetadataRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetDataMetadataRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetDataMetadataRequest, UObjectsMetadataResponse>(
	const int64&, UGetDataMetadataRequest*, FOnGetDataMetadataSuccess, FOnGetDataMetadataError, FOnGetDataMetadataComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetDataMetadataRequest, UObjectsMetadataResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetDataMetadataRequest*, FOnGetDataMetadataSuccess, FOnGetDataMetadataError, FOnGetDataMetadataComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetDataMetadataRequest*, TBeamFullResponseHandler<UGetDataMetadataRequest*, UObjectsMetadataResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetDataMetadataRequest*,
                                                                                   TBeamFullResponseHandler<UGetDataMetadataRequest*, UObjectsMetadataResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostDataDownloadURLFromPortalRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostDataDownloadURLFromPortalRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostDataDownloadURLFromPortalRequest, UURLSResponse>(
	const int64&, UPostDataDownloadURLFromPortalRequest*, FOnPostDataDownloadURLFromPortalSuccess, FOnPostDataDownloadURLFromPortalError, FOnPostDataDownloadURLFromPortalComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostDataDownloadURLFromPortalRequest, UURLSResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostDataDownloadURLFromPortalRequest*, FOnPostDataDownloadURLFromPortalSuccess, FOnPostDataDownloadURLFromPortalError, FOnPostDataDownloadURLFromPortalComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostDataDownloadURLFromPortalRequest*, TBeamFullResponseHandler<UPostDataDownloadURLFromPortalRequest*, UURLSResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostDataDownloadURLFromPortalRequest*,
                                                                                   TBeamFullResponseHandler<UPostDataDownloadURLFromPortalRequest*, UURLSResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutDataMoveRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutDataMoveRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutDataMoveRequest, UCloudsavingBasicManifest>(
	const int64&, UPutDataMoveRequest*, FOnPutDataMoveSuccess, FOnPutDataMoveError, FOnPutDataMoveComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutDataMoveRequest, UCloudsavingBasicManifest>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutDataMoveRequest*, FOnPutDataMoveSuccess, FOnPutDataMoveError, FOnPutDataMoveComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutDataMoveRequest*, TBeamFullResponseHandler<UPutDataMoveRequest*, UCloudsavingBasicManifest*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutDataMoveRequest*,
                                                                                   TBeamFullResponseHandler<UPutDataMoveRequest*, UCloudsavingBasicManifest*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutDataMoveFromPortalRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutDataMoveFromPortalRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutDataMoveFromPortalRequest, UCloudsavingBasicManifest>(
	const int64&, UPutDataMoveFromPortalRequest*, FOnPutDataMoveFromPortalSuccess, FOnPutDataMoveFromPortalError, FOnPutDataMoveFromPortalComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutDataMoveFromPortalRequest, UCloudsavingBasicManifest>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutDataMoveFromPortalRequest*, FOnPutDataMoveFromPortalSuccess, FOnPutDataMoveFromPortalError, FOnPutDataMoveFromPortalComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutDataMoveFromPortalRequest*, TBeamFullResponseHandler<UPutDataMoveFromPortalRequest*, UCloudsavingBasicManifest*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutDataMoveFromPortalRequest*,
                                                                                   TBeamFullResponseHandler<UPutDataMoveFromPortalRequest*, UCloudsavingBasicManifest*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostDataUploadURLFromPortalRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostDataUploadURLFromPortalRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostDataUploadURLFromPortalRequest, UURLSResponse>(
	const int64&, UPostDataUploadURLFromPortalRequest*, FOnPostDataUploadURLFromPortalSuccess, FOnPostDataUploadURLFromPortalError, FOnPostDataUploadURLFromPortalComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostDataUploadURLFromPortalRequest, UURLSResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostDataUploadURLFromPortalRequest*, FOnPostDataUploadURLFromPortalSuccess, FOnPostDataUploadURLFromPortalError, FOnPostDataUploadURLFromPortalComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostDataUploadURLFromPortalRequest*, TBeamFullResponseHandler<UPostDataUploadURLFromPortalRequest*, UURLSResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostDataUploadURLFromPortalRequest*,
                                                                                   TBeamFullResponseHandler<UPostDataUploadURLFromPortalRequest*, UURLSResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutDataCommitManifestRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutDataCommitManifestRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutDataCommitManifestRequest, UCloudsavingBasicManifest>(
	const int64&, UPutDataCommitManifestRequest*, FOnPutDataCommitManifestSuccess, FOnPutDataCommitManifestError, FOnPutDataCommitManifestComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutDataCommitManifestRequest, UCloudsavingBasicManifest>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutDataCommitManifestRequest*, FOnPutDataCommitManifestSuccess, FOnPutDataCommitManifestError, FOnPutDataCommitManifestComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutDataCommitManifestRequest*, TBeamFullResponseHandler<UPutDataCommitManifestRequest*, UCloudsavingBasicManifest*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutDataCommitManifestRequest*,
                                                                                   TBeamFullResponseHandler<UPutDataCommitManifestRequest*, UCloudsavingBasicManifest*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostDataUploadURLRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostDataUploadURLRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostDataUploadURLRequest, UURLSResponse>(
	const int64&, UPostDataUploadURLRequest*, FOnPostDataUploadURLSuccess, FOnPostDataUploadURLError, FOnPostDataUploadURLComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostDataUploadURLRequest, UURLSResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostDataUploadURLRequest*, FOnPostDataUploadURLSuccess, FOnPostDataUploadURLError, FOnPostDataUploadURLComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostDataUploadURLRequest*, TBeamFullResponseHandler<UPostDataUploadURLRequest*, UURLSResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostDataUploadURLRequest*,
                                                                                   TBeamFullResponseHandler<UPostDataUploadURLRequest*, UURLSResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostWindowsPurchaseTrackRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostWindowsPurchaseTrackRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostWindowsPurchaseTrackRequest, UPaymentResultResponse>(
	const int64&, UPostWindowsPurchaseTrackRequest*, FOnPostWindowsPurchaseTrackSuccess, FOnPostWindowsPurchaseTrackError, FOnPostWindowsPurchaseTrackComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostWindowsPurchaseTrackRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostWindowsPurchaseTrackRequest*, FOnPostWindowsPurchaseTrackSuccess, FOnPostWindowsPurchaseTrackError, FOnPostWindowsPurchaseTrackComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostWindowsPurchaseTrackRequest*, TBeamFullResponseHandler<UPostWindowsPurchaseTrackRequest*, UPaymentResultResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostWindowsPurchaseTrackRequest*,
                                                                                   TBeamFullResponseHandler<UPostWindowsPurchaseTrackRequest*, UPaymentResultResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetAuditsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetAuditsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetAuditsRequest, UListAuditResponse>(
	const int64&, UGetAuditsRequest*, FOnGetAuditsSuccess, FOnGetAuditsError, FOnGetAuditsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetAuditsRequest, UListAuditResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetAuditsRequest*, FOnGetAuditsSuccess, FOnGetAuditsError, FOnGetAuditsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetAuditsRequest*, TBeamFullResponseHandler<UGetAuditsRequest*, UListAuditResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetAuditsRequest*,
                                                                                   TBeamFullResponseHandler<UGetAuditsRequest*, UListAuditResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostWindowsPurchaseCompleteRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostWindowsPurchaseCompleteRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostWindowsPurchaseCompleteRequest, UPaymentResultResponse>(
	const int64&, UPostWindowsPurchaseCompleteRequest*, FOnPostWindowsPurchaseCompleteSuccess, FOnPostWindowsPurchaseCompleteError, FOnPostWindowsPurchaseCompleteComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostWindowsPurchaseCompleteRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostWindowsPurchaseCompleteRequest*, FOnPostWindowsPurchaseCompleteSuccess, FOnPostWindowsPurchaseCompleteError, FOnPostWindowsPurchaseCompleteComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostWindowsPurchaseCompleteRequest*, TBeamFullResponseHandler<UPostWindowsPurchaseCompleteRequest*, UPaymentResultResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostWindowsPurchaseCompleteRequest*,
                                                                                   TBeamFullResponseHandler<UPostWindowsPurchaseCompleteRequest*, UPaymentResultResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetFacebookUpdateRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetFacebookUpdateRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetFacebookUpdateRequest, UBeamPlainTextResponseBody>(
	const int64&, UGetFacebookUpdateRequest*, FOnGetFacebookUpdateSuccess, FOnGetFacebookUpdateError, FOnGetFacebookUpdateComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetFacebookUpdateRequest, UBeamPlainTextResponseBody>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetFacebookUpdateRequest*, FOnGetFacebookUpdateSuccess, FOnGetFacebookUpdateError, FOnGetFacebookUpdateComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetFacebookUpdateRequest*, TBeamFullResponseHandler<UGetFacebookUpdateRequest*, UBeamPlainTextResponseBody*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetFacebookUpdateRequest*,
                                                                                   TBeamFullResponseHandler<UGetFacebookUpdateRequest*, UBeamPlainTextResponseBody*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostFacebookUpdateRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostFacebookUpdateRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostFacebookUpdateRequest, UBeamPlainTextResponseBody>(
	const int64&, UPostFacebookUpdateRequest*, FOnPostFacebookUpdateSuccess, FOnPostFacebookUpdateError, FOnPostFacebookUpdateComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostFacebookUpdateRequest, UBeamPlainTextResponseBody>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostFacebookUpdateRequest*, FOnPostFacebookUpdateSuccess, FOnPostFacebookUpdateError, FOnPostFacebookUpdateComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostFacebookUpdateRequest*, TBeamFullResponseHandler<UPostFacebookUpdateRequest*, UBeamPlainTextResponseBody*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostFacebookUpdateRequest*,
                                                                                   TBeamFullResponseHandler<UPostFacebookUpdateRequest*, UBeamPlainTextResponseBody*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostFacebookPurchaseCompleteRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostFacebookPurchaseCompleteRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostFacebookPurchaseCompleteRequest, UPaymentResultResponse>(
	const int64&, UPostFacebookPurchaseCompleteRequest*, FOnPostFacebookPurchaseCompleteSuccess, FOnPostFacebookPurchaseCompleteError, FOnPostFacebookPurchaseCompleteComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostFacebookPurchaseCompleteRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostFacebookPurchaseCompleteRequest*, FOnPostFacebookPurchaseCompleteSuccess, FOnPostFacebookPurchaseCompleteError, FOnPostFacebookPurchaseCompleteComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostFacebookPurchaseCompleteRequest*, TBeamFullResponseHandler<UPostFacebookPurchaseCompleteRequest*, UPaymentResultResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostFacebookPurchaseCompleteRequest*,
                                                                                   TBeamFullResponseHandler<UPostFacebookPurchaseCompleteRequest*, UPaymentResultResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostTestPurchaseCompleteRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostTestPurchaseCompleteRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostTestPurchaseCompleteRequest, UPaymentResultResponse>(
	const int64&, UPostTestPurchaseCompleteRequest*, FOnPostTestPurchaseCompleteSuccess, FOnPostTestPurchaseCompleteError, FOnPostTestPurchaseCompleteComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostTestPurchaseCompleteRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostTestPurchaseCompleteRequest*, FOnPostTestPurchaseCompleteSuccess, FOnPostTestPurchaseCompleteError, FOnPostTestPurchaseCompleteComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostTestPurchaseCompleteRequest*, TBeamFullResponseHandler<UPostTestPurchaseCompleteRequest*, UPaymentResultResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostTestPurchaseCompleteRequest*,
                                                                                   TBeamFullResponseHandler<UPostTestPurchaseCompleteRequest*, UPaymentResultResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetItunesProductRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetItunesProductRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetItunesProductRequest, UGetProductResponse>(
	const int64&, UGetItunesProductRequest*, FOnGetItunesProductSuccess, FOnGetItunesProductError, FOnGetItunesProductComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetItunesProductRequest, UGetProductResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetItunesProductRequest*, FOnGetItunesProductSuccess, FOnGetItunesProductError, FOnGetItunesProductComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetItunesProductRequest*, TBeamFullResponseHandler<UGetItunesProductRequest*, UGetProductResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetItunesProductRequest*,
                                                                                   TBeamFullResponseHandler<UGetItunesProductRequest*, UGetProductResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostGoogleplayPurchaseCompleteRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostGoogleplayPurchaseCompleteRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostGoogleplayPurchaseCompleteRequest, UPaymentResultResponse>(
	const int64&, UPostGoogleplayPurchaseCompleteRequest*, FOnPostGoogleplayPurchaseCompleteSuccess, FOnPostGoogleplayPurchaseCompleteError, FOnPostGoogleplayPurchaseCompleteComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostGoogleplayPurchaseCompleteRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostGoogleplayPurchaseCompleteRequest*, FOnPostGoogleplayPurchaseCompleteSuccess, FOnPostGoogleplayPurchaseCompleteError, FOnPostGoogleplayPurchaseCompleteComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostGoogleplayPurchaseCompleteRequest*, TBeamFullResponseHandler<UPostGoogleplayPurchaseCompleteRequest*, UPaymentResultResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostGoogleplayPurchaseCompleteRequest*,
                                                                                   TBeamFullResponseHandler<UPostGoogleplayPurchaseCompleteRequest*, UPaymentResultResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostTestPurchaseTrackRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostTestPurchaseTrackRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostTestPurchaseTrackRequest, UPaymentResultResponse>(
	const int64&, UPostTestPurchaseTrackRequest*, FOnPostTestPurchaseTrackSuccess, FOnPostTestPurchaseTrackError, FOnPostTestPurchaseTrackComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostTestPurchaseTrackRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostTestPurchaseTrackRequest*, FOnPostTestPurchaseTrackSuccess, FOnPostTestPurchaseTrackError, FOnPostTestPurchaseTrackComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostTestPurchaseTrackRequest*, TBeamFullResponseHandler<UPostTestPurchaseTrackRequest*, UPaymentResultResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostTestPurchaseTrackRequest*,
                                                                                   TBeamFullResponseHandler<UPostTestPurchaseTrackRequest*, UPaymentResultResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostGoogleplayPurchaseVerifyRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostGoogleplayPurchaseVerifyRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostGoogleplayPurchaseVerifyRequest, UPaymentResultResponse>(
	const int64&, UPostGoogleplayPurchaseVerifyRequest*, FOnPostGoogleplayPurchaseVerifySuccess, FOnPostGoogleplayPurchaseVerifyError, FOnPostGoogleplayPurchaseVerifyComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostGoogleplayPurchaseVerifyRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostGoogleplayPurchaseVerifyRequest*, FOnPostGoogleplayPurchaseVerifySuccess, FOnPostGoogleplayPurchaseVerifyError, FOnPostGoogleplayPurchaseVerifyComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostGoogleplayPurchaseVerifyRequest*, TBeamFullResponseHandler<UPostGoogleplayPurchaseVerifyRequest*, UPaymentResultResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostGoogleplayPurchaseVerifyRequest*,
                                                                                   TBeamFullResponseHandler<UPostGoogleplayPurchaseVerifyRequest*, UPaymentResultResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostCouponPurchaseTrackRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostCouponPurchaseTrackRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostCouponPurchaseTrackRequest, UPaymentResultResponse>(
	const int64&, UPostCouponPurchaseTrackRequest*, FOnPostCouponPurchaseTrackSuccess, FOnPostCouponPurchaseTrackError, FOnPostCouponPurchaseTrackComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostCouponPurchaseTrackRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostCouponPurchaseTrackRequest*, FOnPostCouponPurchaseTrackSuccess, FOnPostCouponPurchaseTrackError, FOnPostCouponPurchaseTrackComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostCouponPurchaseTrackRequest*, TBeamFullResponseHandler<UPostCouponPurchaseTrackRequest*, UPaymentResultResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostCouponPurchaseTrackRequest*,
                                                                                   TBeamFullResponseHandler<UPostCouponPurchaseTrackRequest*, UPaymentResultResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostSteamPurchaseCompleteRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostSteamPurchaseCompleteRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostSteamPurchaseCompleteRequest, UPaymentResultResponse>(
	const int64&, UPostSteamPurchaseCompleteRequest*, FOnPostSteamPurchaseCompleteSuccess, FOnPostSteamPurchaseCompleteError, FOnPostSteamPurchaseCompleteComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostSteamPurchaseCompleteRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostSteamPurchaseCompleteRequest*, FOnPostSteamPurchaseCompleteSuccess, FOnPostSteamPurchaseCompleteError, FOnPostSteamPurchaseCompleteComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostSteamPurchaseCompleteRequest*, TBeamFullResponseHandler<UPostSteamPurchaseCompleteRequest*, UPaymentResultResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostSteamPurchaseCompleteRequest*,
                                                                                   TBeamFullResponseHandler<UPostSteamPurchaseCompleteRequest*, UPaymentResultResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostFacebookPurchaseTrackRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostFacebookPurchaseTrackRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostFacebookPurchaseTrackRequest, UPaymentResultResponse>(
	const int64&, UPostFacebookPurchaseTrackRequest*, FOnPostFacebookPurchaseTrackSuccess, FOnPostFacebookPurchaseTrackError, FOnPostFacebookPurchaseTrackComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostFacebookPurchaseTrackRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostFacebookPurchaseTrackRequest*, FOnPostFacebookPurchaseTrackSuccess, FOnPostFacebookPurchaseTrackError, FOnPostFacebookPurchaseTrackComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostFacebookPurchaseTrackRequest*, TBeamFullResponseHandler<UPostFacebookPurchaseTrackRequest*, UPaymentResultResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostFacebookPurchaseTrackRequest*,
                                                                                   TBeamFullResponseHandler<UPostFacebookPurchaseTrackRequest*, UPaymentResultResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostTestPurchaseVerifyRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostTestPurchaseVerifyRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostTestPurchaseVerifyRequest, UPaymentResultResponse>(
	const int64&, UPostTestPurchaseVerifyRequest*, FOnPostTestPurchaseVerifySuccess, FOnPostTestPurchaseVerifyError, FOnPostTestPurchaseVerifyComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostTestPurchaseVerifyRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostTestPurchaseVerifyRequest*, FOnPostTestPurchaseVerifySuccess, FOnPostTestPurchaseVerifyError, FOnPostTestPurchaseVerifyComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostTestPurchaseVerifyRequest*, TBeamFullResponseHandler<UPostTestPurchaseVerifyRequest*, UPaymentResultResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostTestPurchaseVerifyRequest*,
                                                                                   TBeamFullResponseHandler<UPostTestPurchaseVerifyRequest*, UPaymentResultResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostGoogleplayPurchaseTrackRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostGoogleplayPurchaseTrackRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostGoogleplayPurchaseTrackRequest, UPaymentResultResponse>(
	const int64&, UPostGoogleplayPurchaseTrackRequest*, FOnPostGoogleplayPurchaseTrackSuccess, FOnPostGoogleplayPurchaseTrackError, FOnPostGoogleplayPurchaseTrackComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostGoogleplayPurchaseTrackRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostGoogleplayPurchaseTrackRequest*, FOnPostGoogleplayPurchaseTrackSuccess, FOnPostGoogleplayPurchaseTrackError, FOnPostGoogleplayPurchaseTrackComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostGoogleplayPurchaseTrackRequest*, TBeamFullResponseHandler<UPostGoogleplayPurchaseTrackRequest*, UPaymentResultResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostGoogleplayPurchaseTrackRequest*,
                                                                                   TBeamFullResponseHandler<UPostGoogleplayPurchaseTrackRequest*, UPaymentResultResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetSteamPricesRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetSteamPricesRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetSteamPricesRequest, ULocalizedPriceMap>(
	const int64&, UGetSteamPricesRequest*, FOnGetSteamPricesSuccess, FOnGetSteamPricesError, FOnGetSteamPricesComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetSteamPricesRequest, ULocalizedPriceMap>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetSteamPricesRequest*, FOnGetSteamPricesSuccess, FOnGetSteamPricesError, FOnGetSteamPricesComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetSteamPricesRequest*, TBeamFullResponseHandler<UGetSteamPricesRequest*, ULocalizedPriceMap*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetSteamPricesRequest*,
                                                                                   TBeamFullResponseHandler<UGetSteamPricesRequest*, ULocalizedPriceMap*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostWindowsPurchaseVerifyRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostWindowsPurchaseVerifyRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostWindowsPurchaseVerifyRequest, UPaymentResultResponse>(
	const int64&, UPostWindowsPurchaseVerifyRequest*, FOnPostWindowsPurchaseVerifySuccess, FOnPostWindowsPurchaseVerifyError, FOnPostWindowsPurchaseVerifyComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostWindowsPurchaseVerifyRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostWindowsPurchaseVerifyRequest*, FOnPostWindowsPurchaseVerifySuccess, FOnPostWindowsPurchaseVerifyError, FOnPostWindowsPurchaseVerifyComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostWindowsPurchaseVerifyRequest*, TBeamFullResponseHandler<UPostWindowsPurchaseVerifyRequest*, UPaymentResultResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostWindowsPurchaseVerifyRequest*,
                                                                                   TBeamFullResponseHandler<UPostWindowsPurchaseVerifyRequest*, UPaymentResultResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostItunesPurchaseVerifyRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostItunesPurchaseVerifyRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostItunesPurchaseVerifyRequest, UPaymentResultResponse>(
	const int64&, UPostItunesPurchaseVerifyRequest*, FOnPostItunesPurchaseVerifySuccess, FOnPostItunesPurchaseVerifyError, FOnPostItunesPurchaseVerifyComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostItunesPurchaseVerifyRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostItunesPurchaseVerifyRequest*, FOnPostItunesPurchaseVerifySuccess, FOnPostItunesPurchaseVerifyError, FOnPostItunesPurchaseVerifyComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostItunesPurchaseVerifyRequest*, TBeamFullResponseHandler<UPostItunesPurchaseVerifyRequest*, UPaymentResultResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostItunesPurchaseVerifyRequest*,
                                                                                   TBeamFullResponseHandler<UPostItunesPurchaseVerifyRequest*, UPaymentResultResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostItunesPurchaseCompleteRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostItunesPurchaseCompleteRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostItunesPurchaseCompleteRequest, UPaymentResultResponse>(
	const int64&, UPostItunesPurchaseCompleteRequest*, FOnPostItunesPurchaseCompleteSuccess, FOnPostItunesPurchaseCompleteError, FOnPostItunesPurchaseCompleteComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostItunesPurchaseCompleteRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostItunesPurchaseCompleteRequest*, FOnPostItunesPurchaseCompleteSuccess, FOnPostItunesPurchaseCompleteError, FOnPostItunesPurchaseCompleteComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostItunesPurchaseCompleteRequest*, TBeamFullResponseHandler<UPostItunesPurchaseCompleteRequest*, UPaymentResultResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostItunesPurchaseCompleteRequest*,
                                                                                   TBeamFullResponseHandler<UPostItunesPurchaseCompleteRequest*, UPaymentResultResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostFacebookPurchaseVerifyRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostFacebookPurchaseVerifyRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostFacebookPurchaseVerifyRequest, UPaymentResultResponse>(
	const int64&, UPostFacebookPurchaseVerifyRequest*, FOnPostFacebookPurchaseVerifySuccess, FOnPostFacebookPurchaseVerifyError, FOnPostFacebookPurchaseVerifyComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostFacebookPurchaseVerifyRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostFacebookPurchaseVerifyRequest*, FOnPostFacebookPurchaseVerifySuccess, FOnPostFacebookPurchaseVerifyError, FOnPostFacebookPurchaseVerifyComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostFacebookPurchaseVerifyRequest*, TBeamFullResponseHandler<UPostFacebookPurchaseVerifyRequest*, UPaymentResultResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostFacebookPurchaseVerifyRequest*,
                                                                                   TBeamFullResponseHandler<UPostFacebookPurchaseVerifyRequest*, UPaymentResultResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostSteamPurchaseTrackRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostSteamPurchaseTrackRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostSteamPurchaseTrackRequest, UPaymentResultResponse>(
	const int64&, UPostSteamPurchaseTrackRequest*, FOnPostSteamPurchaseTrackSuccess, FOnPostSteamPurchaseTrackError, FOnPostSteamPurchaseTrackComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostSteamPurchaseTrackRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostSteamPurchaseTrackRequest*, FOnPostSteamPurchaseTrackSuccess, FOnPostSteamPurchaseTrackError, FOnPostSteamPurchaseTrackComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostSteamPurchaseTrackRequest*, TBeamFullResponseHandler<UPostSteamPurchaseTrackRequest*, UPaymentResultResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostSteamPurchaseTrackRequest*,
                                                                                   TBeamFullResponseHandler<UPostSteamPurchaseTrackRequest*, UPaymentResultResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostCouponPurchaseVerifyRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostCouponPurchaseVerifyRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostCouponPurchaseVerifyRequest, UPaymentResultResponse>(
	const int64&, UPostCouponPurchaseVerifyRequest*, FOnPostCouponPurchaseVerifySuccess, FOnPostCouponPurchaseVerifyError, FOnPostCouponPurchaseVerifyComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostCouponPurchaseVerifyRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostCouponPurchaseVerifyRequest*, FOnPostCouponPurchaseVerifySuccess, FOnPostCouponPurchaseVerifyError, FOnPostCouponPurchaseVerifyComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostCouponPurchaseVerifyRequest*, TBeamFullResponseHandler<UPostCouponPurchaseVerifyRequest*, UPaymentResultResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostCouponPurchaseVerifyRequest*,
                                                                                   TBeamFullResponseHandler<UPostCouponPurchaseVerifyRequest*, UPaymentResultResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetWindowsProductRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetWindowsProductRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetWindowsProductRequest, UGetProductResponse>(
	const int64&, UGetWindowsProductRequest*, FOnGetWindowsProductSuccess, FOnGetWindowsProductError, FOnGetWindowsProductComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetWindowsProductRequest, UGetProductResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetWindowsProductRequest*, FOnGetWindowsProductSuccess, FOnGetWindowsProductError, FOnGetWindowsProductComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetWindowsProductRequest*, TBeamFullResponseHandler<UGetWindowsProductRequest*, UGetProductResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetWindowsProductRequest*,
                                                                                   TBeamFullResponseHandler<UGetWindowsProductRequest*, UGetProductResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetFacebookProductRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetFacebookProductRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetFacebookProductRequest, UGetProductResponse>(
	const int64&, UGetFacebookProductRequest*, FOnGetFacebookProductSuccess, FOnGetFacebookProductError, FOnGetFacebookProductComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetFacebookProductRequest, UGetProductResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetFacebookProductRequest*, FOnGetFacebookProductSuccess, FOnGetFacebookProductError, FOnGetFacebookProductComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetFacebookProductRequest*, TBeamFullResponseHandler<UGetFacebookProductRequest*, UGetProductResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetFacebookProductRequest*,
                                                                                   TBeamFullResponseHandler<UGetFacebookProductRequest*, UGetProductResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetCouponProductRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetCouponProductRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetCouponProductRequest, UGetProductResponse>(
	const int64&, UGetCouponProductRequest*, FOnGetCouponProductSuccess, FOnGetCouponProductError, FOnGetCouponProductComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetCouponProductRequest, UGetProductResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetCouponProductRequest*, FOnGetCouponProductSuccess, FOnGetCouponProductError, FOnGetCouponProductComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetCouponProductRequest*, TBeamFullResponseHandler<UGetCouponProductRequest*, UGetProductResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetCouponProductRequest*,
                                                                                   TBeamFullResponseHandler<UGetCouponProductRequest*, UGetProductResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetSteamProductsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetSteamProductsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetSteamProductsRequest, UGetProductsResponse>(
	const int64&, UGetSteamProductsRequest*, FOnGetSteamProductsSuccess, FOnGetSteamProductsError, FOnGetSteamProductsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetSteamProductsRequest, UGetProductsResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetSteamProductsRequest*, FOnGetSteamProductsSuccess, FOnGetSteamProductsError, FOnGetSteamProductsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetSteamProductsRequest*, TBeamFullResponseHandler<UGetSteamProductsRequest*, UGetProductsResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetSteamProductsRequest*,
                                                                                   TBeamFullResponseHandler<UGetSteamProductsRequest*, UGetProductsResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostSteamAuthRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostSteamAuthRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostSteamAuthRequest, UEmptyResponse>(
	const int64&, UPostSteamAuthRequest*, FOnPostSteamAuthSuccess, FOnPostSteamAuthError, FOnPostSteamAuthComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostSteamAuthRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostSteamAuthRequest*, FOnPostSteamAuthSuccess, FOnPostSteamAuthError, FOnPostSteamAuthComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostSteamAuthRequest*, TBeamFullResponseHandler<UPostSteamAuthRequest*, UEmptyResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostSteamAuthRequest*,
                                                                                   TBeamFullResponseHandler<UPostSteamAuthRequest*, UEmptyResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetSteamProductRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetSteamProductRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetSteamProductRequest, UGetProductResponse>(
	const int64&, UGetSteamProductRequest*, FOnGetSteamProductSuccess, FOnGetSteamProductError, FOnGetSteamProductComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetSteamProductRequest, UGetProductResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetSteamProductRequest*, FOnGetSteamProductSuccess, FOnGetSteamProductError, FOnGetSteamProductComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetSteamProductRequest*, TBeamFullResponseHandler<UGetSteamProductRequest*, UGetProductResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetSteamProductRequest*,
                                                                                   TBeamFullResponseHandler<UGetSteamProductRequest*, UGetProductResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostCouponPurchaseCompleteRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostCouponPurchaseCompleteRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostCouponPurchaseCompleteRequest, UPaymentResultResponse>(
	const int64&, UPostCouponPurchaseCompleteRequest*, FOnPostCouponPurchaseCompleteSuccess, FOnPostCouponPurchaseCompleteError, FOnPostCouponPurchaseCompleteComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostCouponPurchaseCompleteRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostCouponPurchaseCompleteRequest*, FOnPostCouponPurchaseCompleteSuccess, FOnPostCouponPurchaseCompleteError, FOnPostCouponPurchaseCompleteComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostCouponPurchaseCompleteRequest*, TBeamFullResponseHandler<UPostCouponPurchaseCompleteRequest*, UPaymentResultResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostCouponPurchaseCompleteRequest*,
                                                                                   TBeamFullResponseHandler<UPostCouponPurchaseCompleteRequest*, UPaymentResultResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetGoogleplayProductRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetGoogleplayProductRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetGoogleplayProductRequest, UGetProductResponse>(
	const int64&, UGetGoogleplayProductRequest*, FOnGetGoogleplayProductSuccess, FOnGetGoogleplayProductError, FOnGetGoogleplayProductComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetGoogleplayProductRequest, UGetProductResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetGoogleplayProductRequest*, FOnGetGoogleplayProductSuccess, FOnGetGoogleplayProductError, FOnGetGoogleplayProductComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetGoogleplayProductRequest*, TBeamFullResponseHandler<UGetGoogleplayProductRequest*, UGetProductResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetGoogleplayProductRequest*,
                                                                                   TBeamFullResponseHandler<UGetGoogleplayProductRequest*, UGetProductResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetTestProductRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetTestProductRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetTestProductRequest, UGetProductResponse>(
	const int64&, UGetTestProductRequest*, FOnGetTestProductSuccess, FOnGetTestProductError, FOnGetTestProductComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetTestProductRequest, UGetProductResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetTestProductRequest*, FOnGetTestProductSuccess, FOnGetTestProductError, FOnGetTestProductComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetTestProductRequest*, TBeamFullResponseHandler<UGetTestProductRequest*, UGetProductResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetTestProductRequest*,
                                                                                   TBeamFullResponseHandler<UGetTestProductRequest*, UGetProductResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostSteamPurchaseVerifyRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostSteamPurchaseVerifyRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostSteamPurchaseVerifyRequest, UPaymentResultResponse>(
	const int64&, UPostSteamPurchaseVerifyRequest*, FOnPostSteamPurchaseVerifySuccess, FOnPostSteamPurchaseVerifyError, FOnPostSteamPurchaseVerifyComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostSteamPurchaseVerifyRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostSteamPurchaseVerifyRequest*, FOnPostSteamPurchaseVerifySuccess, FOnPostSteamPurchaseVerifyError, FOnPostSteamPurchaseVerifyComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostSteamPurchaseVerifyRequest*, TBeamFullResponseHandler<UPostSteamPurchaseVerifyRequest*, UPaymentResultResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostSteamPurchaseVerifyRequest*,
                                                                                   TBeamFullResponseHandler<UPostSteamPurchaseVerifyRequest*, UPaymentResultResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostItunesPurchaseTrackRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostItunesPurchaseTrackRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostItunesPurchaseTrackRequest, UPaymentResultResponse>(
	const int64&, UPostItunesPurchaseTrackRequest*, FOnPostItunesPurchaseTrackSuccess, FOnPostItunesPurchaseTrackError, FOnPostItunesPurchaseTrackComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostItunesPurchaseTrackRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostItunesPurchaseTrackRequest*, FOnPostItunesPurchaseTrackSuccess, FOnPostItunesPurchaseTrackError, FOnPostItunesPurchaseTrackComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostItunesPurchaseTrackRequest*, TBeamFullResponseHandler<UPostItunesPurchaseTrackRequest*, UPaymentResultResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostItunesPurchaseTrackRequest*,
                                                                                   TBeamFullResponseHandler<UPostItunesPurchaseTrackRequest*, UPaymentResultResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetPaymentsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetPaymentsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetPaymentsRequest, UCommonResponse>(
	const int64&, UGetPaymentsRequest*, FOnGetPaymentsSuccess, FOnGetPaymentsError, FOnGetPaymentsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetPaymentsRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetPaymentsRequest*, FOnGetPaymentsSuccess, FOnGetPaymentsError, FOnGetPaymentsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetPaymentsRequest*, TBeamFullResponseHandler<UGetPaymentsRequest*, UCommonResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetPaymentsRequest*,
                                                                                   TBeamFullResponseHandler<UGetPaymentsRequest*, UCommonResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostTestPurchaseBeginRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostTestPurchaseBeginRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostTestPurchaseBeginRequest, UBeginPurchaseResponse>(
	const int64&, UPostTestPurchaseBeginRequest*, FOnPostTestPurchaseBeginSuccess, FOnPostTestPurchaseBeginError, FOnPostTestPurchaseBeginComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostTestPurchaseBeginRequest, UBeginPurchaseResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostTestPurchaseBeginRequest*, FOnPostTestPurchaseBeginSuccess, FOnPostTestPurchaseBeginError, FOnPostTestPurchaseBeginComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostTestPurchaseBeginRequest*, TBeamFullResponseHandler<UPostTestPurchaseBeginRequest*, UBeginPurchaseResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostTestPurchaseBeginRequest*,
                                                                                   TBeamFullResponseHandler<UPostTestPurchaseBeginRequest*, UBeginPurchaseResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostSteamPurchaseFailRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostSteamPurchaseFailRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostSteamPurchaseFailRequest, UPaymentResultResponse>(
	const int64&, UPostSteamPurchaseFailRequest*, FOnPostSteamPurchaseFailSuccess, FOnPostSteamPurchaseFailError, FOnPostSteamPurchaseFailComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostSteamPurchaseFailRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostSteamPurchaseFailRequest*, FOnPostSteamPurchaseFailSuccess, FOnPostSteamPurchaseFailError, FOnPostSteamPurchaseFailComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostSteamPurchaseFailRequest*, TBeamFullResponseHandler<UPostSteamPurchaseFailRequest*, UPaymentResultResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostSteamPurchaseFailRequest*,
                                                                                   TBeamFullResponseHandler<UPostSteamPurchaseFailRequest*, UPaymentResultResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostFacebookPurchaseFailRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostFacebookPurchaseFailRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostFacebookPurchaseFailRequest, UPaymentResultResponse>(
	const int64&, UPostFacebookPurchaseFailRequest*, FOnPostFacebookPurchaseFailSuccess, FOnPostFacebookPurchaseFailError, FOnPostFacebookPurchaseFailComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostFacebookPurchaseFailRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostFacebookPurchaseFailRequest*, FOnPostFacebookPurchaseFailSuccess, FOnPostFacebookPurchaseFailError, FOnPostFacebookPurchaseFailComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostFacebookPurchaseFailRequest*, TBeamFullResponseHandler<UPostFacebookPurchaseFailRequest*, UPaymentResultResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostFacebookPurchaseFailRequest*,
                                                                                   TBeamFullResponseHandler<UPostFacebookPurchaseFailRequest*, UPaymentResultResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostGoogleplayPurchaseBeginRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostGoogleplayPurchaseBeginRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostGoogleplayPurchaseBeginRequest, UBeginPurchaseResponse>(
	const int64&, UPostGoogleplayPurchaseBeginRequest*, FOnPostGoogleplayPurchaseBeginSuccess, FOnPostGoogleplayPurchaseBeginError, FOnPostGoogleplayPurchaseBeginComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostGoogleplayPurchaseBeginRequest, UBeginPurchaseResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostGoogleplayPurchaseBeginRequest*, FOnPostGoogleplayPurchaseBeginSuccess, FOnPostGoogleplayPurchaseBeginError, FOnPostGoogleplayPurchaseBeginComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostGoogleplayPurchaseBeginRequest*, TBeamFullResponseHandler<UPostGoogleplayPurchaseBeginRequest*, UBeginPurchaseResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostGoogleplayPurchaseBeginRequest*,
                                                                                   TBeamFullResponseHandler<UPostGoogleplayPurchaseBeginRequest*, UBeginPurchaseResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostItunesPurchaseBeginRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostItunesPurchaseBeginRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostItunesPurchaseBeginRequest, UBeginPurchaseResponse>(
	const int64&, UPostItunesPurchaseBeginRequest*, FOnPostItunesPurchaseBeginSuccess, FOnPostItunesPurchaseBeginError, FOnPostItunesPurchaseBeginComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostItunesPurchaseBeginRequest, UBeginPurchaseResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostItunesPurchaseBeginRequest*, FOnPostItunesPurchaseBeginSuccess, FOnPostItunesPurchaseBeginError, FOnPostItunesPurchaseBeginComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostItunesPurchaseBeginRequest*, TBeamFullResponseHandler<UPostItunesPurchaseBeginRequest*, UBeginPurchaseResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostItunesPurchaseBeginRequest*,
                                                                                   TBeamFullResponseHandler<UPostItunesPurchaseBeginRequest*, UBeginPurchaseResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostFacebookPurchaseCancelRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostFacebookPurchaseCancelRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostFacebookPurchaseCancelRequest, UPaymentResultResponse>(
	const int64&, UPostFacebookPurchaseCancelRequest*, FOnPostFacebookPurchaseCancelSuccess, FOnPostFacebookPurchaseCancelError, FOnPostFacebookPurchaseCancelComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostFacebookPurchaseCancelRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostFacebookPurchaseCancelRequest*, FOnPostFacebookPurchaseCancelSuccess, FOnPostFacebookPurchaseCancelError, FOnPostFacebookPurchaseCancelComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostFacebookPurchaseCancelRequest*, TBeamFullResponseHandler<UPostFacebookPurchaseCancelRequest*, UPaymentResultResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostFacebookPurchaseCancelRequest*,
                                                                                   TBeamFullResponseHandler<UPostFacebookPurchaseCancelRequest*, UPaymentResultResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostItunesPurchaseFailRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostItunesPurchaseFailRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostItunesPurchaseFailRequest, UPaymentResultResponse>(
	const int64&, UPostItunesPurchaseFailRequest*, FOnPostItunesPurchaseFailSuccess, FOnPostItunesPurchaseFailError, FOnPostItunesPurchaseFailComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostItunesPurchaseFailRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostItunesPurchaseFailRequest*, FOnPostItunesPurchaseFailSuccess, FOnPostItunesPurchaseFailError, FOnPostItunesPurchaseFailComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostItunesPurchaseFailRequest*, TBeamFullResponseHandler<UPostItunesPurchaseFailRequest*, UPaymentResultResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostItunesPurchaseFailRequest*,
                                                                                   TBeamFullResponseHandler<UPostItunesPurchaseFailRequest*, UPaymentResultResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostTestPurchaseCancelRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostTestPurchaseCancelRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostTestPurchaseCancelRequest, UPaymentResultResponse>(
	const int64&, UPostTestPurchaseCancelRequest*, FOnPostTestPurchaseCancelSuccess, FOnPostTestPurchaseCancelError, FOnPostTestPurchaseCancelComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostTestPurchaseCancelRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostTestPurchaseCancelRequest*, FOnPostTestPurchaseCancelSuccess, FOnPostTestPurchaseCancelError, FOnPostTestPurchaseCancelComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostTestPurchaseCancelRequest*, TBeamFullResponseHandler<UPostTestPurchaseCancelRequest*, UPaymentResultResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostTestPurchaseCancelRequest*,
                                                                                   TBeamFullResponseHandler<UPostTestPurchaseCancelRequest*, UPaymentResultResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostTestPurchaseFailRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostTestPurchaseFailRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostTestPurchaseFailRequest, UPaymentResultResponse>(
	const int64&, UPostTestPurchaseFailRequest*, FOnPostTestPurchaseFailSuccess, FOnPostTestPurchaseFailError, FOnPostTestPurchaseFailComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostTestPurchaseFailRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostTestPurchaseFailRequest*, FOnPostTestPurchaseFailSuccess, FOnPostTestPurchaseFailError, FOnPostTestPurchaseFailComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostTestPurchaseFailRequest*, TBeamFullResponseHandler<UPostTestPurchaseFailRequest*, UPaymentResultResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostTestPurchaseFailRequest*,
                                                                                   TBeamFullResponseHandler<UPostTestPurchaseFailRequest*, UPaymentResultResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostCouponPurchaseCancelRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostCouponPurchaseCancelRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostCouponPurchaseCancelRequest, UPaymentResultResponse>(
	const int64&, UPostCouponPurchaseCancelRequest*, FOnPostCouponPurchaseCancelSuccess, FOnPostCouponPurchaseCancelError, FOnPostCouponPurchaseCancelComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostCouponPurchaseCancelRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostCouponPurchaseCancelRequest*, FOnPostCouponPurchaseCancelSuccess, FOnPostCouponPurchaseCancelError, FOnPostCouponPurchaseCancelComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostCouponPurchaseCancelRequest*, TBeamFullResponseHandler<UPostCouponPurchaseCancelRequest*, UPaymentResultResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostCouponPurchaseCancelRequest*,
                                                                                   TBeamFullResponseHandler<UPostCouponPurchaseCancelRequest*, UPaymentResultResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostCouponPurchaseBeginRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostCouponPurchaseBeginRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostCouponPurchaseBeginRequest, UBeginPurchaseResponse>(
	const int64&, UPostCouponPurchaseBeginRequest*, FOnPostCouponPurchaseBeginSuccess, FOnPostCouponPurchaseBeginError, FOnPostCouponPurchaseBeginComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostCouponPurchaseBeginRequest, UBeginPurchaseResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostCouponPurchaseBeginRequest*, FOnPostCouponPurchaseBeginSuccess, FOnPostCouponPurchaseBeginError, FOnPostCouponPurchaseBeginComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostCouponPurchaseBeginRequest*, TBeamFullResponseHandler<UPostCouponPurchaseBeginRequest*, UBeginPurchaseResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostCouponPurchaseBeginRequest*,
                                                                                   TBeamFullResponseHandler<UPostCouponPurchaseBeginRequest*, UBeginPurchaseResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostFacebookPurchaseBeginRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostFacebookPurchaseBeginRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostFacebookPurchaseBeginRequest, UBeginPurchaseResponse>(
	const int64&, UPostFacebookPurchaseBeginRequest*, FOnPostFacebookPurchaseBeginSuccess, FOnPostFacebookPurchaseBeginError, FOnPostFacebookPurchaseBeginComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostFacebookPurchaseBeginRequest, UBeginPurchaseResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostFacebookPurchaseBeginRequest*, FOnPostFacebookPurchaseBeginSuccess, FOnPostFacebookPurchaseBeginError, FOnPostFacebookPurchaseBeginComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostFacebookPurchaseBeginRequest*, TBeamFullResponseHandler<UPostFacebookPurchaseBeginRequest*, UBeginPurchaseResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostFacebookPurchaseBeginRequest*,
                                                                                   TBeamFullResponseHandler<UPostFacebookPurchaseBeginRequest*, UBeginPurchaseResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetSteamOrderRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetSteamOrderRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetSteamOrderRequest, USteamOrderInfoResponse>(
	const int64&, UGetSteamOrderRequest*, FOnGetSteamOrderSuccess, FOnGetSteamOrderError, FOnGetSteamOrderComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetSteamOrderRequest, USteamOrderInfoResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetSteamOrderRequest*, FOnGetSteamOrderSuccess, FOnGetSteamOrderError, FOnGetSteamOrderComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetSteamOrderRequest*, TBeamFullResponseHandler<UGetSteamOrderRequest*, USteamOrderInfoResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetSteamOrderRequest*,
                                                                                   TBeamFullResponseHandler<UGetSteamOrderRequest*, USteamOrderInfoResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostWindowsPurchaseBeginRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostWindowsPurchaseBeginRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostWindowsPurchaseBeginRequest, UBeginPurchaseResponse>(
	const int64&, UPostWindowsPurchaseBeginRequest*, FOnPostWindowsPurchaseBeginSuccess, FOnPostWindowsPurchaseBeginError, FOnPostWindowsPurchaseBeginComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostWindowsPurchaseBeginRequest, UBeginPurchaseResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostWindowsPurchaseBeginRequest*, FOnPostWindowsPurchaseBeginSuccess, FOnPostWindowsPurchaseBeginError, FOnPostWindowsPurchaseBeginComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostWindowsPurchaseBeginRequest*, TBeamFullResponseHandler<UPostWindowsPurchaseBeginRequest*, UBeginPurchaseResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostWindowsPurchaseBeginRequest*,
                                                                                   TBeamFullResponseHandler<UPostWindowsPurchaseBeginRequest*, UBeginPurchaseResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostGoogleplayPurchaseFailRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostGoogleplayPurchaseFailRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostGoogleplayPurchaseFailRequest, UPaymentResultResponse>(
	const int64&, UPostGoogleplayPurchaseFailRequest*, FOnPostGoogleplayPurchaseFailSuccess, FOnPostGoogleplayPurchaseFailError, FOnPostGoogleplayPurchaseFailComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostGoogleplayPurchaseFailRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostGoogleplayPurchaseFailRequest*, FOnPostGoogleplayPurchaseFailSuccess, FOnPostGoogleplayPurchaseFailError, FOnPostGoogleplayPurchaseFailComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostGoogleplayPurchaseFailRequest*, TBeamFullResponseHandler<UPostGoogleplayPurchaseFailRequest*, UPaymentResultResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostGoogleplayPurchaseFailRequest*,
                                                                                   TBeamFullResponseHandler<UPostGoogleplayPurchaseFailRequest*, UPaymentResultResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostGoogleplayPurchaseCancelRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostGoogleplayPurchaseCancelRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostGoogleplayPurchaseCancelRequest, UPaymentResultResponse>(
	const int64&, UPostGoogleplayPurchaseCancelRequest*, FOnPostGoogleplayPurchaseCancelSuccess, FOnPostGoogleplayPurchaseCancelError, FOnPostGoogleplayPurchaseCancelComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostGoogleplayPurchaseCancelRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostGoogleplayPurchaseCancelRequest*, FOnPostGoogleplayPurchaseCancelSuccess, FOnPostGoogleplayPurchaseCancelError, FOnPostGoogleplayPurchaseCancelComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostGoogleplayPurchaseCancelRequest*, TBeamFullResponseHandler<UPostGoogleplayPurchaseCancelRequest*, UPaymentResultResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostGoogleplayPurchaseCancelRequest*,
                                                                                   TBeamFullResponseHandler<UPostGoogleplayPurchaseCancelRequest*, UPaymentResultResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostCouponPurchaseFailRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostCouponPurchaseFailRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostCouponPurchaseFailRequest, UPaymentResultResponse>(
	const int64&, UPostCouponPurchaseFailRequest*, FOnPostCouponPurchaseFailSuccess, FOnPostCouponPurchaseFailError, FOnPostCouponPurchaseFailComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostCouponPurchaseFailRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostCouponPurchaseFailRequest*, FOnPostCouponPurchaseFailSuccess, FOnPostCouponPurchaseFailError, FOnPostCouponPurchaseFailComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostCouponPurchaseFailRequest*, TBeamFullResponseHandler<UPostCouponPurchaseFailRequest*, UPaymentResultResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostCouponPurchaseFailRequest*,
                                                                                   TBeamFullResponseHandler<UPostCouponPurchaseFailRequest*, UPaymentResultResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostSteamPurchaseBeginRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostSteamPurchaseBeginRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostSteamPurchaseBeginRequest, UBeginPurchaseResponse>(
	const int64&, UPostSteamPurchaseBeginRequest*, FOnPostSteamPurchaseBeginSuccess, FOnPostSteamPurchaseBeginError, FOnPostSteamPurchaseBeginComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostSteamPurchaseBeginRequest, UBeginPurchaseResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostSteamPurchaseBeginRequest*, FOnPostSteamPurchaseBeginSuccess, FOnPostSteamPurchaseBeginError, FOnPostSteamPurchaseBeginComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostSteamPurchaseBeginRequest*, TBeamFullResponseHandler<UPostSteamPurchaseBeginRequest*, UBeginPurchaseResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostSteamPurchaseBeginRequest*,
                                                                                   TBeamFullResponseHandler<UPostSteamPurchaseBeginRequest*, UBeginPurchaseResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostSteamPurchaseCancelRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostSteamPurchaseCancelRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostSteamPurchaseCancelRequest, UPaymentResultResponse>(
	const int64&, UPostSteamPurchaseCancelRequest*, FOnPostSteamPurchaseCancelSuccess, FOnPostSteamPurchaseCancelError, FOnPostSteamPurchaseCancelComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostSteamPurchaseCancelRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostSteamPurchaseCancelRequest*, FOnPostSteamPurchaseCancelSuccess, FOnPostSteamPurchaseCancelError, FOnPostSteamPurchaseCancelComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostSteamPurchaseCancelRequest*, TBeamFullResponseHandler<UPostSteamPurchaseCancelRequest*, UPaymentResultResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostSteamPurchaseCancelRequest*,
                                                                                   TBeamFullResponseHandler<UPostSteamPurchaseCancelRequest*, UPaymentResultResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostWindowsPurchaseCancelRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostWindowsPurchaseCancelRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostWindowsPurchaseCancelRequest, UPaymentResultResponse>(
	const int64&, UPostWindowsPurchaseCancelRequest*, FOnPostWindowsPurchaseCancelSuccess, FOnPostWindowsPurchaseCancelError, FOnPostWindowsPurchaseCancelComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostWindowsPurchaseCancelRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostWindowsPurchaseCancelRequest*, FOnPostWindowsPurchaseCancelSuccess, FOnPostWindowsPurchaseCancelError, FOnPostWindowsPurchaseCancelComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostWindowsPurchaseCancelRequest*, TBeamFullResponseHandler<UPostWindowsPurchaseCancelRequest*, UPaymentResultResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostWindowsPurchaseCancelRequest*,
                                                                                   TBeamFullResponseHandler<UPostWindowsPurchaseCancelRequest*, UPaymentResultResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostWindowsPurchaseFailRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostWindowsPurchaseFailRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostWindowsPurchaseFailRequest, UPaymentResultResponse>(
	const int64&, UPostWindowsPurchaseFailRequest*, FOnPostWindowsPurchaseFailSuccess, FOnPostWindowsPurchaseFailError, FOnPostWindowsPurchaseFailComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostWindowsPurchaseFailRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostWindowsPurchaseFailRequest*, FOnPostWindowsPurchaseFailSuccess, FOnPostWindowsPurchaseFailError, FOnPostWindowsPurchaseFailComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostWindowsPurchaseFailRequest*, TBeamFullResponseHandler<UPostWindowsPurchaseFailRequest*, UPaymentResultResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostWindowsPurchaseFailRequest*,
                                                                                   TBeamFullResponseHandler<UPostWindowsPurchaseFailRequest*, UPaymentResultResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostItunesPurchaseCancelRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostItunesPurchaseCancelRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostItunesPurchaseCancelRequest, UPaymentResultResponse>(
	const int64&, UPostItunesPurchaseCancelRequest*, FOnPostItunesPurchaseCancelSuccess, FOnPostItunesPurchaseCancelError, FOnPostItunesPurchaseCancelComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostItunesPurchaseCancelRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostItunesPurchaseCancelRequest*, FOnPostItunesPurchaseCancelSuccess, FOnPostItunesPurchaseCancelError, FOnPostItunesPurchaseCancelComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostItunesPurchaseCancelRequest*, TBeamFullResponseHandler<UPostItunesPurchaseCancelRequest*, UPaymentResultResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostItunesPurchaseCancelRequest*,
                                                                                   TBeamFullResponseHandler<UPostItunesPurchaseCancelRequest*, UPaymentResultResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UBasicPushPostRegisterRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UBasicPushPostRegisterRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UBasicPushPostRegisterRequest, UEmptyRsp>(
	const int64&, UBasicPushPostRegisterRequest*, FOnBasicPushPostRegisterSuccess, FOnBasicPushPostRegisterError, FOnBasicPushPostRegisterComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UBasicPushPostRegisterRequest, UEmptyRsp>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicPushPostRegisterRequest*, FOnBasicPushPostRegisterSuccess, FOnBasicPushPostRegisterError, FOnBasicPushPostRegisterComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UBasicPushPostRegisterRequest*, TBeamFullResponseHandler<UBasicPushPostRegisterRequest*, UEmptyRsp*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicPushPostRegisterRequest*,
                                                                                   TBeamFullResponseHandler<UBasicPushPostRegisterRequest*, UEmptyRsp*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostSendRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostSendRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostSendRequest, UEmptyRsp>(
	const int64&, UPostSendRequest*, FOnPostSendSuccess, FOnPostSendError, FOnPostSendComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostSendRequest, UEmptyRsp>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostSendRequest*, FOnPostSendSuccess, FOnPostSendError, FOnPostSendComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostSendRequest*, TBeamFullResponseHandler<UPostSendRequest*, UEmptyRsp*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostSendRequest*,
                                                                                   TBeamFullResponseHandler<UPostSendRequest*, UEmptyRsp*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostPlayerRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostPlayerRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostPlayerRequest, UCommonResponse>(
	const int64&, UPostPlayerRequest*, FOnPostPlayerSuccess, FOnPostPlayerError, FOnPostPlayerComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostPlayerRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostPlayerRequest*, FOnPostPlayerSuccess, FOnPostPlayerError, FOnPostPlayerComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostPlayerRequest*, TBeamFullResponseHandler<UPostPlayerRequest*, UCommonResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostPlayerRequest*,
                                                                                   TBeamFullResponseHandler<UPostPlayerRequest*, UCommonResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostCustomRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostCustomRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostCustomRequest, UCommonResponse>(
	const int64&, UPostCustomRequest*, FOnPostCustomSuccess, FOnPostCustomError, FOnPostCustomComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostCustomRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostCustomRequest*, FOnPostCustomSuccess, FOnPostCustomError, FOnPostCustomComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostCustomRequest*, TBeamFullResponseHandler<UPostCustomRequest*, UCommonResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostCustomRequest*,
                                                                                   TBeamFullResponseHandler<UPostCustomRequest*, UCommonResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostServerRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostServerRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostServerRequest, UCommonResponse>(
	const int64&, UPostServerRequest*, FOnPostServerSuccess, FOnPostServerError, FOnPostServerComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostServerRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostServerRequest*, FOnPostServerSuccess, FOnPostServerError, FOnPostServerComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostServerRequest*, TBeamFullResponseHandler<UPostServerRequest*, UCommonResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostServerRequest*,
                                                                                   TBeamFullResponseHandler<UPostServerRequest*, UCommonResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostGenericRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostGenericRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostGenericRequest, UCommonResponse>(
	const int64&, UPostGenericRequest*, FOnPostGenericSuccess, FOnPostGenericError, FOnPostGenericComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostGenericRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostGenericRequest*, FOnPostGenericSuccess, FOnPostGenericError, FOnPostGenericComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostGenericRequest*, TBeamFullResponseHandler<UPostGenericRequest*, UCommonResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostGenericRequest*,
                                                                                   TBeamFullResponseHandler<UPostGenericRequest*, UCommonResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetNotificationRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetNotificationRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetNotificationRequest, USubscriberDetailsResponse>(
	const int64&, UGetNotificationRequest*, FOnGetNotificationSuccess, FOnGetNotificationError, FOnGetNotificationComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetNotificationRequest, USubscriberDetailsResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetNotificationRequest*, FOnGetNotificationSuccess, FOnGetNotificationError, FOnGetNotificationComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetNotificationRequest*, TBeamFullResponseHandler<UGetNotificationRequest*, USubscriberDetailsResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetNotificationRequest*,
                                                                                   TBeamFullResponseHandler<UGetNotificationRequest*, USubscriberDetailsResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UBasicNotificationPostGameRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UBasicNotificationPostGameRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UBasicNotificationPostGameRequest, UCommonResponse>(
	const int64&, UBasicNotificationPostGameRequest*, FOnBasicNotificationPostGameSuccess, FOnBasicNotificationPostGameError, FOnBasicNotificationPostGameComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UBasicNotificationPostGameRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicNotificationPostGameRequest*, FOnBasicNotificationPostGameSuccess, FOnBasicNotificationPostGameError, FOnBasicNotificationPostGameComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UBasicNotificationPostGameRequest*, TBeamFullResponseHandler<UBasicNotificationPostGameRequest*, UCommonResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicNotificationPostGameRequest*,
                                                                                   TBeamFullResponseHandler<UBasicNotificationPostGameRequest*, UCommonResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetCustomerAliasAvailableRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetCustomerAliasAvailableRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetCustomerAliasAvailableRequest, UAliasAvailableResponse>(
	const int64&, UGetCustomerAliasAvailableRequest*, FOnGetCustomerAliasAvailableSuccess, FOnGetCustomerAliasAvailableError, FOnGetCustomerAliasAvailableComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetCustomerAliasAvailableRequest, UAliasAvailableResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetCustomerAliasAvailableRequest*, FOnGetCustomerAliasAvailableSuccess, FOnGetCustomerAliasAvailableError, FOnGetCustomerAliasAvailableComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetCustomerAliasAvailableRequest*, TBeamFullResponseHandler<UGetCustomerAliasAvailableRequest*, UAliasAvailableResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetCustomerAliasAvailableRequest*,
                                                                                   TBeamFullResponseHandler<UGetCustomerAliasAvailableRequest*, UAliasAvailableResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetProjectRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetProjectRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetProjectRequest, UProjectView>(
	const int64&, UGetProjectRequest*, FOnGetProjectSuccess, FOnGetProjectError, FOnGetProjectComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetProjectRequest, UProjectView>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetProjectRequest*, FOnGetProjectSuccess, FOnGetProjectError, FOnGetProjectComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetProjectRequest*, TBeamFullResponseHandler<UGetProjectRequest*, UProjectView*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetProjectRequest*,
                                                                                   TBeamFullResponseHandler<UGetProjectRequest*, UProjectView*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetClientDefaultsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetClientDefaultsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetClientDefaultsRequest, URealmConfiguration>(
	const int64&, UGetClientDefaultsRequest*, FOnGetClientDefaultsSuccess, FOnGetClientDefaultsError, FOnGetClientDefaultsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetClientDefaultsRequest, URealmConfiguration>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetClientDefaultsRequest*, FOnGetClientDefaultsSuccess, FOnGetClientDefaultsError, FOnGetClientDefaultsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetClientDefaultsRequest*, TBeamFullResponseHandler<UGetClientDefaultsRequest*, URealmConfiguration*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetClientDefaultsRequest*,
                                                                                   TBeamFullResponseHandler<UGetClientDefaultsRequest*, URealmConfiguration*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostCustomerRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostCustomerRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostCustomerRequest, UNewCustomerResponse>(
	const int64&, UPostCustomerRequest*, FOnPostCustomerSuccess, FOnPostCustomerError, FOnPostCustomerComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostCustomerRequest, UNewCustomerResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostCustomerRequest*, FOnPostCustomerSuccess, FOnPostCustomerError, FOnPostCustomerComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostCustomerRequest*, TBeamFullResponseHandler<UPostCustomerRequest*, UNewCustomerResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostCustomerRequest*,
                                                                                   TBeamFullResponseHandler<UPostCustomerRequest*, UNewCustomerResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetIsCustomerRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetIsCustomerRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetIsCustomerRequest, UEmptyResponse>(
	const int64&, UGetIsCustomerRequest*, FOnGetIsCustomerSuccess, FOnGetIsCustomerError, FOnGetIsCustomerComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetIsCustomerRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetIsCustomerRequest*, FOnGetIsCustomerSuccess, FOnGetIsCustomerError, FOnGetIsCustomerComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetIsCustomerRequest*, TBeamFullResponseHandler<UGetIsCustomerRequest*, UEmptyResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetIsCustomerRequest*,
                                                                                   TBeamFullResponseHandler<UGetIsCustomerRequest*, UEmptyResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetCustomersRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetCustomersRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetCustomersRequest, UCustomersResponse>(
	const int64&, UGetCustomersRequest*, FOnGetCustomersSuccess, FOnGetCustomersError, FOnGetCustomersComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetCustomersRequest, UCustomersResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetCustomersRequest*, FOnGetCustomersSuccess, FOnGetCustomersError, FOnGetCustomersComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetCustomersRequest*, TBeamFullResponseHandler<UGetCustomersRequest*, UCustomersResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetCustomersRequest*,
                                                                                   TBeamFullResponseHandler<UGetCustomersRequest*, UCustomersResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostProjectBeamableRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostProjectBeamableRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostProjectBeamableRequest, UCommonResponse>(
	const int64&, UPostProjectBeamableRequest*, FOnPostProjectBeamableSuccess, FOnPostProjectBeamableError, FOnPostProjectBeamableComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostProjectBeamableRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostProjectBeamableRequest*, FOnPostProjectBeamableSuccess, FOnPostProjectBeamableError, FOnPostProjectBeamableComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostProjectBeamableRequest*, TBeamFullResponseHandler<UPostProjectBeamableRequest*, UCommonResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostProjectBeamableRequest*,
                                                                                   TBeamFullResponseHandler<UPostProjectBeamableRequest*, UCommonResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostProjectRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostProjectRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostProjectRequest, UCommonResponse>(
	const int64&, UPostProjectRequest*, FOnPostProjectSuccess, FOnPostProjectError, FOnPostProjectComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostProjectRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostProjectRequest*, FOnPostProjectSuccess, FOnPostProjectError, FOnPostProjectComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostProjectRequest*, TBeamFullResponseHandler<UPostProjectRequest*, UCommonResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostProjectRequest*,
                                                                                   TBeamFullResponseHandler<UPostProjectRequest*, UCommonResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutProjectRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutProjectRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutProjectRequest, UCommonResponse>(
	const int64&, UPutProjectRequest*, FOnPutProjectSuccess, FOnPutProjectError, FOnPutProjectComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutProjectRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutProjectRequest*, FOnPutProjectSuccess, FOnPutProjectError, FOnPutProjectComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutProjectRequest*, TBeamFullResponseHandler<UPutProjectRequest*, UCommonResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutProjectRequest*,
                                                                                   TBeamFullResponseHandler<UPutProjectRequest*, UCommonResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UDeleteProjectRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UDeleteProjectRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UDeleteProjectRequest, UCommonResponse>(
	const int64&, UDeleteProjectRequest*, FOnDeleteProjectSuccess, FOnDeleteProjectError, FOnDeleteProjectComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UDeleteProjectRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteProjectRequest*, FOnDeleteProjectSuccess, FOnDeleteProjectError, FOnDeleteProjectComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UDeleteProjectRequest*, TBeamFullResponseHandler<UDeleteProjectRequest*, UCommonResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteProjectRequest*,
                                                                                   TBeamFullResponseHandler<UDeleteProjectRequest*, UCommonResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetGamesRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetGamesRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetGamesRequest, UGetGameResponse>(
	const int64&, UGetGamesRequest*, FOnGetGamesSuccess, FOnGetGamesError, FOnGetGamesComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetGamesRequest, UGetGameResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetGamesRequest*, FOnGetGamesSuccess, FOnGetGamesError, FOnGetGamesComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetGamesRequest*, TBeamFullResponseHandler<UGetGamesRequest*, UGetGameResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetGamesRequest*,
                                                                                   TBeamFullResponseHandler<UGetGamesRequest*, UGetGameResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetConfigRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetConfigRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetConfigRequest, URealmConfigResponse>(
	const int64&, UGetConfigRequest*, FOnGetConfigSuccess, FOnGetConfigError, FOnGetConfigComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetConfigRequest, URealmConfigResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetConfigRequest*, FOnGetConfigSuccess, FOnGetConfigError, FOnGetConfigComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetConfigRequest*, TBeamFullResponseHandler<UGetConfigRequest*, URealmConfigResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetConfigRequest*,
                                                                                   TBeamFullResponseHandler<UGetConfigRequest*, URealmConfigResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutConfigRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutConfigRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutConfigRequest, UCommonResponse>(
	const int64&, UPutConfigRequest*, FOnPutConfigSuccess, FOnPutConfigError, FOnPutConfigComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutConfigRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutConfigRequest*, FOnPutConfigSuccess, FOnPutConfigError, FOnPutConfigComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutConfigRequest*, TBeamFullResponseHandler<UPutConfigRequest*, UCommonResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutConfigRequest*,
                                                                                   TBeamFullResponseHandler<UPutConfigRequest*, UCommonResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutProjectRenameRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutProjectRenameRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutProjectRenameRequest, UCommonResponse>(
	const int64&, UPutProjectRenameRequest*, FOnPutProjectRenameSuccess, FOnPutProjectRenameError, FOnPutProjectRenameComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutProjectRenameRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutProjectRenameRequest*, FOnPutProjectRenameSuccess, FOnPutProjectRenameError, FOnPutProjectRenameComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutProjectRenameRequest*, TBeamFullResponseHandler<UPutProjectRenameRequest*, UCommonResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutProjectRenameRequest*,
                                                                                   TBeamFullResponseHandler<UPutProjectRenameRequest*, UCommonResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetPlansRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetPlansRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetPlansRequest, UServicePlansResponse>(
	const int64&, UGetPlansRequest*, FOnGetPlansSuccess, FOnGetPlansError, FOnGetPlansComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetPlansRequest, UServicePlansResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetPlansRequest*, FOnGetPlansSuccess, FOnGetPlansError, FOnGetPlansComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetPlansRequest*, TBeamFullResponseHandler<UGetPlansRequest*, UServicePlansResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetPlansRequest*,
                                                                                   TBeamFullResponseHandler<UGetPlansRequest*, UServicePlansResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostPlansRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostPlansRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostPlansRequest, UCommonResponse>(
	const int64&, UPostPlansRequest*, FOnPostPlansSuccess, FOnPostPlansError, FOnPostPlansComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostPlansRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostPlansRequest*, FOnPostPlansSuccess, FOnPostPlansError, FOnPostPlansComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostPlansRequest*, TBeamFullResponseHandler<UPostPlansRequest*, UCommonResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostPlansRequest*,
                                                                                   TBeamFullResponseHandler<UPostPlansRequest*, UCommonResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetCustomerRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetCustomerRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetCustomerRequest, UCustomerViewResponse>(
	const int64&, UGetCustomerRequest*, FOnGetCustomerSuccess, FOnGetCustomerError, FOnGetCustomerComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetCustomerRequest, UCustomerViewResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetCustomerRequest*, FOnGetCustomerSuccess, FOnGetCustomerError, FOnGetCustomerComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetCustomerRequest*, TBeamFullResponseHandler<UGetCustomerRequest*, UCustomerViewResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetCustomerRequest*,
                                                                                   TBeamFullResponseHandler<UGetCustomerRequest*, UCustomerViewResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetLaunchMessageRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetLaunchMessageRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetLaunchMessageRequest, ULaunchMessageListResponse>(
	const int64&, UGetLaunchMessageRequest*, FOnGetLaunchMessageSuccess, FOnGetLaunchMessageError, FOnGetLaunchMessageComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetLaunchMessageRequest, ULaunchMessageListResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetLaunchMessageRequest*, FOnGetLaunchMessageSuccess, FOnGetLaunchMessageError, FOnGetLaunchMessageComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetLaunchMessageRequest*, TBeamFullResponseHandler<UGetLaunchMessageRequest*, ULaunchMessageListResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetLaunchMessageRequest*,
                                                                                   TBeamFullResponseHandler<UGetLaunchMessageRequest*, ULaunchMessageListResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostLaunchMessageRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostLaunchMessageRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostLaunchMessageRequest, UCommonResponse>(
	const int64&, UPostLaunchMessageRequest*, FOnPostLaunchMessageSuccess, FOnPostLaunchMessageError, FOnPostLaunchMessageComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostLaunchMessageRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostLaunchMessageRequest*, FOnPostLaunchMessageSuccess, FOnPostLaunchMessageError, FOnPostLaunchMessageComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostLaunchMessageRequest*, TBeamFullResponseHandler<UPostLaunchMessageRequest*, UCommonResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostLaunchMessageRequest*,
                                                                                   TBeamFullResponseHandler<UPostLaunchMessageRequest*, UCommonResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UDeleteLaunchMessageRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UDeleteLaunchMessageRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UDeleteLaunchMessageRequest, UCommonResponse>(
	const int64&, UDeleteLaunchMessageRequest*, FOnDeleteLaunchMessageSuccess, FOnDeleteLaunchMessageError, FOnDeleteLaunchMessageComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UDeleteLaunchMessageRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteLaunchMessageRequest*, FOnDeleteLaunchMessageSuccess, FOnDeleteLaunchMessageError, FOnDeleteLaunchMessageComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UDeleteLaunchMessageRequest*, TBeamFullResponseHandler<UDeleteLaunchMessageRequest*, UCommonResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteLaunchMessageRequest*,
                                                                                   TBeamFullResponseHandler<UDeleteLaunchMessageRequest*, UCommonResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetAdminCustomerRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetAdminCustomerRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetAdminCustomerRequest, UCustomerResponse>(
	const int64&, UGetAdminCustomerRequest*, FOnGetAdminCustomerSuccess, FOnGetAdminCustomerError, FOnGetAdminCustomerComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetAdminCustomerRequest, UCustomerResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetAdminCustomerRequest*, FOnGetAdminCustomerSuccess, FOnGetAdminCustomerError, FOnGetAdminCustomerComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetAdminCustomerRequest*, TBeamFullResponseHandler<UGetAdminCustomerRequest*, UCustomerResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetAdminCustomerRequest*,
                                                                                   TBeamFullResponseHandler<UGetAdminCustomerRequest*, UCustomerResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetGameRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetGameRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetGameRequest, UGetGameResponse>(
	const int64&, UGetGameRequest*, FOnGetGameSuccess, FOnGetGameError, FOnGetGameComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetGameRequest, UGetGameResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetGameRequest*, FOnGetGameSuccess, FOnGetGameError, FOnGetGameComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetGameRequest*, TBeamFullResponseHandler<UGetGameRequest*, UGetGameResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetGameRequest*,
                                                                                   TBeamFullResponseHandler<UGetGameRequest*, UGetGameResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UBasicRealmsPostGameRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UBasicRealmsPostGameRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UBasicRealmsPostGameRequest, UCommonResponse>(
	const int64&, UBasicRealmsPostGameRequest*, FOnBasicRealmsPostGameSuccess, FOnBasicRealmsPostGameError, FOnBasicRealmsPostGameComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UBasicRealmsPostGameRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicRealmsPostGameRequest*, FOnBasicRealmsPostGameSuccess, FOnBasicRealmsPostGameError, FOnBasicRealmsPostGameComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UBasicRealmsPostGameRequest*, TBeamFullResponseHandler<UBasicRealmsPostGameRequest*, UCommonResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicRealmsPostGameRequest*,
                                                                                   TBeamFullResponseHandler<UBasicRealmsPostGameRequest*, UCommonResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutGameRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutGameRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutGameRequest, UCommonResponse>(
	const int64&, UPutGameRequest*, FOnPutGameSuccess, FOnPutGameError, FOnPutGameComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutGameRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutGameRequest*, FOnPutGameSuccess, FOnPutGameError, FOnPutGameComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutGameRequest*, TBeamFullResponseHandler<UPutGameRequest*, UCommonResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutGameRequest*,
                                                                                   TBeamFullResponseHandler<UPutGameRequest*, UCommonResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetProjectPromoteRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetProjectPromoteRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetProjectPromoteRequest, UPromoteRealmResponseOld>(
	const int64&, UGetProjectPromoteRequest*, FOnGetProjectPromoteSuccess, FOnGetProjectPromoteError, FOnGetProjectPromoteComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetProjectPromoteRequest, UPromoteRealmResponseOld>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetProjectPromoteRequest*, FOnGetProjectPromoteSuccess, FOnGetProjectPromoteError, FOnGetProjectPromoteComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetProjectPromoteRequest*, TBeamFullResponseHandler<UGetProjectPromoteRequest*, UPromoteRealmResponseOld*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetProjectPromoteRequest*,
                                                                                   TBeamFullResponseHandler<UGetProjectPromoteRequest*, UPromoteRealmResponseOld*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostProjectPromoteRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostProjectPromoteRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostProjectPromoteRequest, UPromoteRealmResponseOld>(
	const int64&, UPostProjectPromoteRequest*, FOnPostProjectPromoteSuccess, FOnPostProjectPromoteError, FOnPostProjectPromoteComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostProjectPromoteRequest, UPromoteRealmResponseOld>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostProjectPromoteRequest*, FOnPostProjectPromoteSuccess, FOnPostProjectPromoteError, FOnPostProjectPromoteComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostProjectPromoteRequest*, TBeamFullResponseHandler<UPostProjectPromoteRequest*, UPromoteRealmResponseOld*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostProjectPromoteRequest*,
                                                                                   TBeamFullResponseHandler<UPostProjectPromoteRequest*, UPromoteRealmResponseOld*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetPromotionRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetPromotionRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetPromotionRequest, UPromoteRealmResponse>(
	const int64&, UGetPromotionRequest*, FOnGetPromotionSuccess, FOnGetPromotionError, FOnGetPromotionComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetPromotionRequest, UPromoteRealmResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetPromotionRequest*, FOnGetPromotionSuccess, FOnGetPromotionError, FOnGetPromotionComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetPromotionRequest*, TBeamFullResponseHandler<UGetPromotionRequest*, UPromoteRealmResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetPromotionRequest*,
                                                                                   TBeamFullResponseHandler<UGetPromotionRequest*, UPromoteRealmResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostPromotionRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostPromotionRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostPromotionRequest, UPromoteRealmResponse>(
	const int64&, UPostPromotionRequest*, FOnPostPromotionSuccess, FOnPostPromotionError, FOnPostPromotionComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostPromotionRequest, UPromoteRealmResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostPromotionRequest*, FOnPostPromotionSuccess, FOnPostPromotionError, FOnPostPromotionComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostPromotionRequest*, TBeamFullResponseHandler<UPostPromotionRequest*, UPromoteRealmResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostPromotionRequest*,
                                                                                   TBeamFullResponseHandler<UPostPromotionRequest*, UPromoteRealmResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetMyRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetMyRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetMyRequest, USocial>(
	const int64&, UGetMyRequest*, FOnGetMySuccess, FOnGetMyError, FOnGetMyComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetMyRequest, USocial>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetMyRequest*, FOnGetMySuccess, FOnGetMyError, FOnGetMyComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetMyRequest*, TBeamFullResponseHandler<UGetMyRequest*, USocial*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetMyRequest*,
                                                                                   TBeamFullResponseHandler<UGetMyRequest*, USocial*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostFriendsInviteRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostFriendsInviteRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostFriendsInviteRequest, UEmptyResponse>(
	const int64&, UPostFriendsInviteRequest*, FOnPostFriendsInviteSuccess, FOnPostFriendsInviteError, FOnPostFriendsInviteComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostFriendsInviteRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostFriendsInviteRequest*, FOnPostFriendsInviteSuccess, FOnPostFriendsInviteError, FOnPostFriendsInviteComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostFriendsInviteRequest*, TBeamFullResponseHandler<UPostFriendsInviteRequest*, UEmptyResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostFriendsInviteRequest*,
                                                                                   TBeamFullResponseHandler<UPostFriendsInviteRequest*, UEmptyResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UDeleteFriendsInviteRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UDeleteFriendsInviteRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UDeleteFriendsInviteRequest, UEmptyResponse>(
	const int64&, UDeleteFriendsInviteRequest*, FOnDeleteFriendsInviteSuccess, FOnDeleteFriendsInviteError, FOnDeleteFriendsInviteComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UDeleteFriendsInviteRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteFriendsInviteRequest*, FOnDeleteFriendsInviteSuccess, FOnDeleteFriendsInviteError, FOnDeleteFriendsInviteComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UDeleteFriendsInviteRequest*, TBeamFullResponseHandler<UDeleteFriendsInviteRequest*, UEmptyResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteFriendsInviteRequest*,
                                                                                   TBeamFullResponseHandler<UDeleteFriendsInviteRequest*, UEmptyResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UDeleteFriendsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UDeleteFriendsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UDeleteFriendsRequest, UEmptyResponse>(
	const int64&, UDeleteFriendsRequest*, FOnDeleteFriendsSuccess, FOnDeleteFriendsError, FOnDeleteFriendsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UDeleteFriendsRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteFriendsRequest*, FOnDeleteFriendsSuccess, FOnDeleteFriendsError, FOnDeleteFriendsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UDeleteFriendsRequest*, TBeamFullResponseHandler<UDeleteFriendsRequest*, UEmptyResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteFriendsRequest*,
                                                                                   TBeamFullResponseHandler<UDeleteFriendsRequest*, UEmptyResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostFriendsImportRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostFriendsImportRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostFriendsImportRequest, UEmptyResponse>(
	const int64&, UPostFriendsImportRequest*, FOnPostFriendsImportSuccess, FOnPostFriendsImportError, FOnPostFriendsImportComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostFriendsImportRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostFriendsImportRequest*, FOnPostFriendsImportSuccess, FOnPostFriendsImportError, FOnPostFriendsImportComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostFriendsImportRequest*, TBeamFullResponseHandler<UPostFriendsImportRequest*, UEmptyResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostFriendsImportRequest*,
                                                                                   TBeamFullResponseHandler<UPostFriendsImportRequest*, UEmptyResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostFriendsMakeRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostFriendsMakeRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostFriendsMakeRequest, UCommonResponse>(
	const int64&, UPostFriendsMakeRequest*, FOnPostFriendsMakeSuccess, FOnPostFriendsMakeError, FOnPostFriendsMakeComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostFriendsMakeRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostFriendsMakeRequest*, FOnPostFriendsMakeSuccess, FOnPostFriendsMakeError, FOnPostFriendsMakeComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostFriendsMakeRequest*, TBeamFullResponseHandler<UPostFriendsMakeRequest*, UCommonResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostFriendsMakeRequest*,
                                                                                   TBeamFullResponseHandler<UPostFriendsMakeRequest*, UCommonResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetSocialRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetSocialRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetSocialRequest, UGetSocialStatusesResponse>(
	const int64&, UGetSocialRequest*, FOnGetSocialSuccess, FOnGetSocialError, FOnGetSocialComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetSocialRequest, UGetSocialStatusesResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetSocialRequest*, FOnGetSocialSuccess, FOnGetSocialError, FOnGetSocialComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetSocialRequest*, TBeamFullResponseHandler<UGetSocialRequest*, UGetSocialStatusesResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetSocialRequest*,
                                                                                   TBeamFullResponseHandler<UGetSocialRequest*, UGetSocialStatusesResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostBlockedRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostBlockedRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostBlockedRequest, UFriendshipStatus>(
	const int64&, UPostBlockedRequest*, FOnPostBlockedSuccess, FOnPostBlockedError, FOnPostBlockedComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostBlockedRequest, UFriendshipStatus>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostBlockedRequest*, FOnPostBlockedSuccess, FOnPostBlockedError, FOnPostBlockedComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostBlockedRequest*, TBeamFullResponseHandler<UPostBlockedRequest*, UFriendshipStatus*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostBlockedRequest*,
                                                                                   TBeamFullResponseHandler<UPostBlockedRequest*, UFriendshipStatus*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UDeleteBlockedRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UDeleteBlockedRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UDeleteBlockedRequest, UFriendshipStatus>(
	const int64&, UDeleteBlockedRequest*, FOnDeleteBlockedSuccess, FOnDeleteBlockedError, FOnDeleteBlockedComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UDeleteBlockedRequest, UFriendshipStatus>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteBlockedRequest*, FOnDeleteBlockedSuccess, FOnDeleteBlockedError, FOnDeleteBlockedComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UDeleteBlockedRequest*, TBeamFullResponseHandler<UDeleteBlockedRequest*, UFriendshipStatus*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteBlockedRequest*,
                                                                                   TBeamFullResponseHandler<UDeleteBlockedRequest*, UFriendshipStatus*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetRoomsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetRoomsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetRoomsRequest, UGetRoomsResponse>(
	const int64&, UGetRoomsRequest*, FOnGetRoomsSuccess, FOnGetRoomsError, FOnGetRoomsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetRoomsRequest, UGetRoomsResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetRoomsRequest*, FOnGetRoomsSuccess, FOnGetRoomsError, FOnGetRoomsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetRoomsRequest*, TBeamFullResponseHandler<UGetRoomsRequest*, UGetRoomsResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetRoomsRequest*,
                                                                                   TBeamFullResponseHandler<UGetRoomsRequest*, UGetRoomsResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostRoomsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostRoomsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostRoomsRequest, UCreateRoomResponse>(
	const int64&, UPostRoomsRequest*, FOnPostRoomsSuccess, FOnPostRoomsError, FOnPostRoomsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostRoomsRequest, UCreateRoomResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostRoomsRequest*, FOnPostRoomsSuccess, FOnPostRoomsError, FOnPostRoomsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostRoomsRequest*, TBeamFullResponseHandler<UPostRoomsRequest*, UCreateRoomResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostRoomsRequest*,
                                                                                   TBeamFullResponseHandler<UPostRoomsRequest*, UCreateRoomResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UDeleteRoomsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UDeleteRoomsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UDeleteRoomsRequest, ULeaveRoomResponse>(
	const int64&, UDeleteRoomsRequest*, FOnDeleteRoomsSuccess, FOnDeleteRoomsError, FOnDeleteRoomsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UDeleteRoomsRequest, ULeaveRoomResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteRoomsRequest*, FOnDeleteRoomsSuccess, FOnDeleteRoomsError, FOnDeleteRoomsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UDeleteRoomsRequest*, TBeamFullResponseHandler<UDeleteRoomsRequest*, ULeaveRoomResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteRoomsRequest*,
                                                                                   TBeamFullResponseHandler<UDeleteRoomsRequest*, ULeaveRoomResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetChatV2Request*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetChatV2Request*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetChatV2Request, UGetRoomsResponse>(
	const int64&, UGetChatV2Request*, FOnGetChatV2Success, FOnGetChatV2Error, FOnGetChatV2Complete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetChatV2Request, UGetRoomsResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetChatV2Request*, FOnGetChatV2Success, FOnGetChatV2Error, FOnGetChatV2Complete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetChatV2Request*, TBeamFullResponseHandler<UGetChatV2Request*, UGetRoomsResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetChatV2Request*,
                                                                                   TBeamFullResponseHandler<UGetChatV2Request*, UGetRoomsResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostMessagesRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostMessagesRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostMessagesRequest, USendMessageResponse>(
	const int64&, UPostMessagesRequest*, FOnPostMessagesSuccess, FOnPostMessagesError, FOnPostMessagesComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostMessagesRequest, USendMessageResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostMessagesRequest*, FOnPostMessagesSuccess, FOnPostMessagesError, FOnPostMessagesComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostMessagesRequest*, TBeamFullResponseHandler<UPostMessagesRequest*, USendMessageResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostMessagesRequest*,
                                                                                   TBeamFullResponseHandler<UPostMessagesRequest*, USendMessageResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutTickRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutTickRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutTickRequest, UEmptyResponse>(
	const int64&, UPutTickRequest*, FOnPutTickSuccess, FOnPutTickError, FOnPutTickComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutTickRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutTickRequest*, FOnPutTickSuccess, FOnPutTickError, FOnPutTickComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutTickRequest*, TBeamFullResponseHandler<UPutTickRequest*, UEmptyResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutTickRequest*,
                                                                                   TBeamFullResponseHandler<UPutTickRequest*, UEmptyResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetMatchRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetMatchRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetMatchRequest, UMatchUpdate>(
	const int64&, UGetMatchRequest*, FOnGetMatchSuccess, FOnGetMatchError, FOnGetMatchComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetMatchRequest, UMatchUpdate>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetMatchRequest*, FOnGetMatchSuccess, FOnGetMatchError, FOnGetMatchComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetMatchRequest*, TBeamFullResponseHandler<UGetMatchRequest*, UMatchUpdate*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetMatchRequest*,
                                                                                   TBeamFullResponseHandler<UGetMatchRequest*, UMatchUpdate*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostMatchRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostMatchRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostMatchRequest, UMatchUpdate>(
	const int64&, UPostMatchRequest*, FOnPostMatchSuccess, FOnPostMatchError, FOnPostMatchComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostMatchRequest, UMatchUpdate>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostMatchRequest*, FOnPostMatchSuccess, FOnPostMatchError, FOnPostMatchComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostMatchRequest*, TBeamFullResponseHandler<UPostMatchRequest*, UMatchUpdate*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostMatchRequest*,
                                                                                   TBeamFullResponseHandler<UPostMatchRequest*, UMatchUpdate*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UDeleteMatchRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UDeleteMatchRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UDeleteMatchRequest, UEmptyResponse>(
	const int64&, UDeleteMatchRequest*, FOnDeleteMatchSuccess, FOnDeleteMatchError, FOnDeleteMatchComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UDeleteMatchRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteMatchRequest*, FOnDeleteMatchSuccess, FOnDeleteMatchError, FOnDeleteMatchComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UDeleteMatchRequest*, TBeamFullResponseHandler<UDeleteMatchRequest*, UEmptyResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteMatchRequest*,
                                                                                   TBeamFullResponseHandler<UDeleteMatchRequest*, UEmptyResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetSkusRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetSkusRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetSkusRequest, UGetSKUsResponse>(
	const int64&, UGetSkusRequest*, FOnGetSkusSuccess, FOnGetSkusError, FOnGetSkusComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetSkusRequest, UGetSKUsResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetSkusRequest*, FOnGetSkusSuccess, FOnGetSkusError, FOnGetSkusComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetSkusRequest*, TBeamFullResponseHandler<UGetSkusRequest*, UGetSKUsResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetSkusRequest*,
                                                                                   TBeamFullResponseHandler<UGetSkusRequest*, UGetSKUsResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetCouponsCountRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetCouponsCountRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetCouponsCountRequest, UGetTotalCouponResponse>(
	const int64&, UGetCouponsCountRequest*, FOnGetCouponsCountSuccess, FOnGetCouponsCountError, FOnGetCouponsCountComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetCouponsCountRequest, UGetTotalCouponResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetCouponsCountRequest*, FOnGetCouponsCountSuccess, FOnGetCouponsCountError, FOnGetCouponsCountComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetCouponsCountRequest*, TBeamFullResponseHandler<UGetCouponsCountRequest*, UGetTotalCouponResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetCouponsCountRequest*,
                                                                                   TBeamFullResponseHandler<UGetCouponsCountRequest*, UGetTotalCouponResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostCatalogLegacyRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostCatalogLegacyRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostCatalogLegacyRequest, UResultResponse>(
	const int64&, UPostCatalogLegacyRequest*, FOnPostCatalogLegacySuccess, FOnPostCatalogLegacyError, FOnPostCatalogLegacyComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostCatalogLegacyRequest, UResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostCatalogLegacyRequest*, FOnPostCatalogLegacySuccess, FOnPostCatalogLegacyError, FOnPostCatalogLegacyComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostCatalogLegacyRequest*, TBeamFullResponseHandler<UPostCatalogLegacyRequest*, UResultResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostCatalogLegacyRequest*,
                                                                                   TBeamFullResponseHandler<UPostCatalogLegacyRequest*, UResultResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetCatalogRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetCatalogRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetCatalogRequest, UGetCatalogResponse>(
	const int64&, UGetCatalogRequest*, FOnGetCatalogSuccess, FOnGetCatalogError, FOnGetCatalogComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetCatalogRequest, UGetCatalogResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetCatalogRequest*, FOnGetCatalogSuccess, FOnGetCatalogError, FOnGetCatalogComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetCatalogRequest*, TBeamFullResponseHandler<UGetCatalogRequest*, UGetCatalogResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetCatalogRequest*,
                                                                                   TBeamFullResponseHandler<UGetCatalogRequest*, UGetCatalogResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostSkusRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostSkusRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostSkusRequest, UResultResponse>(
	const int64&, UPostSkusRequest*, FOnPostSkusSuccess, FOnPostSkusError, FOnPostSkusComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostSkusRequest, UResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostSkusRequest*, FOnPostSkusSuccess, FOnPostSkusError, FOnPostSkusComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostSkusRequest*, TBeamFullResponseHandler<UPostSkusRequest*, UResultResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostSkusRequest*,
                                                                                   TBeamFullResponseHandler<UPostSkusRequest*, UResultResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetCommerceRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetCommerceRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetCommerceRequest, UGetActiveOffersResponse>(
	const int64&, UGetCommerceRequest*, FOnGetCommerceSuccess, FOnGetCommerceError, FOnGetCommerceComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetCommerceRequest, UGetActiveOffersResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetCommerceRequest*, FOnGetCommerceSuccess, FOnGetCommerceError, FOnGetCommerceComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetCommerceRequest*, TBeamFullResponseHandler<UGetCommerceRequest*, UGetActiveOffersResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetCommerceRequest*,
                                                                                   TBeamFullResponseHandler<UGetCommerceRequest*, UGetActiveOffersResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutListingsCooldownRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutListingsCooldownRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutListingsCooldownRequest, UCommonResponse>(
	const int64&, UPutListingsCooldownRequest*, FOnPutListingsCooldownSuccess, FOnPutListingsCooldownError, FOnPutListingsCooldownComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutListingsCooldownRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutListingsCooldownRequest*, FOnPutListingsCooldownSuccess, FOnPutListingsCooldownError, FOnPutListingsCooldownComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutListingsCooldownRequest*, TBeamFullResponseHandler<UPutListingsCooldownRequest*, UCommonResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutListingsCooldownRequest*,
                                                                                   TBeamFullResponseHandler<UPutListingsCooldownRequest*, UCommonResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetOffersAdminRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetOffersAdminRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetOffersAdminRequest, UGetActiveOffersResponse>(
	const int64&, UGetOffersAdminRequest*, FOnGetOffersAdminSuccess, FOnGetOffersAdminError, FOnGetOffersAdminComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetOffersAdminRequest, UGetActiveOffersResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetOffersAdminRequest*, FOnGetOffersAdminSuccess, FOnGetOffersAdminError, FOnGetOffersAdminComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetOffersAdminRequest*, TBeamFullResponseHandler<UGetOffersAdminRequest*, UGetActiveOffersResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetOffersAdminRequest*,
                                                                                   TBeamFullResponseHandler<UGetOffersAdminRequest*, UGetActiveOffersResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostPurchaseRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostPurchaseRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostPurchaseRequest, UCommonResponse>(
	const int64&, UPostPurchaseRequest*, FOnPostPurchaseSuccess, FOnPostPurchaseError, FOnPostPurchaseComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostPurchaseRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostPurchaseRequest*, FOnPostPurchaseSuccess, FOnPostPurchaseError, FOnPostPurchaseComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostPurchaseRequest*, TBeamFullResponseHandler<UPostPurchaseRequest*, UCommonResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostPurchaseRequest*,
                                                                                   TBeamFullResponseHandler<UPostPurchaseRequest*, UCommonResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutPurchaseRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutPurchaseRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutPurchaseRequest, UResultResponse>(
	const int64&, UPutPurchaseRequest*, FOnPutPurchaseSuccess, FOnPutPurchaseError, FOnPutPurchaseComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutPurchaseRequest, UResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutPurchaseRequest*, FOnPutPurchaseSuccess, FOnPutPurchaseError, FOnPutPurchaseComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutPurchaseRequest*, TBeamFullResponseHandler<UPutPurchaseRequest*, UResultResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutPurchaseRequest*,
                                                                                   TBeamFullResponseHandler<UPutPurchaseRequest*, UResultResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetListingsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetListingsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetListingsRequest, UActiveListingResponse>(
	const int64&, UGetListingsRequest*, FOnGetListingsSuccess, FOnGetListingsError, FOnGetListingsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetListingsRequest, UActiveListingResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetListingsRequest*, FOnGetListingsSuccess, FOnGetListingsError, FOnGetListingsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetListingsRequest*, TBeamFullResponseHandler<UGetListingsRequest*, UActiveListingResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetListingsRequest*,
                                                                                   TBeamFullResponseHandler<UGetListingsRequest*, UActiveListingResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UDeleteStatusRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UDeleteStatusRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UDeleteStatusRequest, UCommonResponse>(
	const int64&, UDeleteStatusRequest*, FOnDeleteStatusSuccess, FOnDeleteStatusError, FOnDeleteStatusComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UDeleteStatusRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteStatusRequest*, FOnDeleteStatusSuccess, FOnDeleteStatusError, FOnDeleteStatusComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UDeleteStatusRequest*, TBeamFullResponseHandler<UDeleteStatusRequest*, UCommonResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteStatusRequest*,
                                                                                   TBeamFullResponseHandler<UDeleteStatusRequest*, UCommonResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostCouponsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostCouponsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostCouponsRequest, UCommonResponse>(
	const int64&, UPostCouponsRequest*, FOnPostCouponsSuccess, FOnPostCouponsError, FOnPostCouponsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostCouponsRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostCouponsRequest*, FOnPostCouponsSuccess, FOnPostCouponsError, FOnPostCouponsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostCouponsRequest*, TBeamFullResponseHandler<UPostCouponsRequest*, UCommonResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostCouponsRequest*,
                                                                                   TBeamFullResponseHandler<UPostCouponsRequest*, UCommonResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostStatsUpdateRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostStatsUpdateRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostStatsUpdateRequest, UCommonResponse>(
	const int64&, UPostStatsUpdateRequest*, FOnPostStatsUpdateSuccess, FOnPostStatsUpdateError, FOnPostStatsUpdateComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostStatsUpdateRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostStatsUpdateRequest*, FOnPostStatsUpdateSuccess, FOnPostStatsUpdateError, FOnPostStatsUpdateComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostStatsUpdateRequest*, TBeamFullResponseHandler<UPostStatsUpdateRequest*, UCommonResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostStatsUpdateRequest*,
                                                                                   TBeamFullResponseHandler<UPostStatsUpdateRequest*, UCommonResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetOffersRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetOffersRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetOffersRequest, UGetActiveOffersResponse>(
	const int64&, UGetOffersRequest*, FOnGetOffersSuccess, FOnGetOffersError, FOnGetOffersComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetOffersRequest, UGetActiveOffersResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetOffersRequest*, FOnGetOffersSuccess, FOnGetOffersError, FOnGetOffersComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetOffersRequest*, TBeamFullResponseHandler<UGetOffersRequest*, UGetActiveOffersResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetOffersRequest*,
                                                                                   TBeamFullResponseHandler<UGetOffersRequest*, UGetActiveOffersResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UObjectCalendarsPostClaimRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UObjectCalendarsPostClaimRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UObjectCalendarsPostClaimRequest, UCommonResponse>(
	const int64&, UObjectCalendarsPostClaimRequest*, FOnObjectCalendarsPostClaimSuccess, FOnObjectCalendarsPostClaimError, FOnObjectCalendarsPostClaimComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UObjectCalendarsPostClaimRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UObjectCalendarsPostClaimRequest*, FOnObjectCalendarsPostClaimSuccess, FOnObjectCalendarsPostClaimError, FOnObjectCalendarsPostClaimComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UObjectCalendarsPostClaimRequest*, TBeamFullResponseHandler<UObjectCalendarsPostClaimRequest*, UCommonResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UObjectCalendarsPostClaimRequest*,
                                                                                   TBeamFullResponseHandler<UObjectCalendarsPostClaimRequest*, UCommonResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetCalendarsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetCalendarsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetCalendarsRequest, UCalendarQueryResponse>(
	const int64&, UGetCalendarsRequest*, FOnGetCalendarsSuccess, FOnGetCalendarsError, FOnGetCalendarsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetCalendarsRequest, UCalendarQueryResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetCalendarsRequest*, FOnGetCalendarsSuccess, FOnGetCalendarsError, FOnGetCalendarsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetCalendarsRequest*, TBeamFullResponseHandler<UGetCalendarsRequest*, UCalendarQueryResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetCalendarsRequest*,
                                                                                   TBeamFullResponseHandler<UGetCalendarsRequest*, UCalendarQueryResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetListTagsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetListTagsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetListTagsRequest, UListTagsResponse>(
	const int64&, UGetListTagsRequest*, FOnGetListTagsSuccess, FOnGetListTagsError, FOnGetListTagsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetListTagsRequest, UListTagsResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetListTagsRequest*, FOnGetListTagsSuccess, FOnGetListTagsError, FOnGetListTagsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetListTagsRequest*, TBeamFullResponseHandler<UGetListTagsRequest*, UListTagsResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetListTagsRequest*,
                                                                                   TBeamFullResponseHandler<UGetListTagsRequest*, UListTagsResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UBasicAnnouncementsGetListRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UBasicAnnouncementsGetListRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UBasicAnnouncementsGetListRequest, UAnnouncementContentResponse>(
	const int64&, UBasicAnnouncementsGetListRequest*, FOnBasicAnnouncementsGetListSuccess, FOnBasicAnnouncementsGetListError, FOnBasicAnnouncementsGetListComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UBasicAnnouncementsGetListRequest, UAnnouncementContentResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicAnnouncementsGetListRequest*, FOnBasicAnnouncementsGetListSuccess, FOnBasicAnnouncementsGetListError, FOnBasicAnnouncementsGetListComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UBasicAnnouncementsGetListRequest*, TBeamFullResponseHandler<UBasicAnnouncementsGetListRequest*, UAnnouncementContentResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicAnnouncementsGetListRequest*,
                                                                                   TBeamFullResponseHandler<UBasicAnnouncementsGetListRequest*, UAnnouncementContentResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UBasicAnnouncementsGetSearchRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UBasicAnnouncementsGetSearchRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UBasicAnnouncementsGetSearchRequest, UAnnouncementContentResponse>(
	const int64&, UBasicAnnouncementsGetSearchRequest*, FOnBasicAnnouncementsGetSearchSuccess, FOnBasicAnnouncementsGetSearchError, FOnBasicAnnouncementsGetSearchComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UBasicAnnouncementsGetSearchRequest, UAnnouncementContentResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicAnnouncementsGetSearchRequest*, FOnBasicAnnouncementsGetSearchSuccess, FOnBasicAnnouncementsGetSearchError, FOnBasicAnnouncementsGetSearchComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UBasicAnnouncementsGetSearchRequest*, TBeamFullResponseHandler<UBasicAnnouncementsGetSearchRequest*, UAnnouncementContentResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicAnnouncementsGetSearchRequest*,
                                                                                   TBeamFullResponseHandler<UBasicAnnouncementsGetSearchRequest*, UAnnouncementContentResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetListDefinitionsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetListDefinitionsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetListDefinitionsRequest, UListDefinitionsResponse>(
	const int64&, UGetListDefinitionsRequest*, FOnGetListDefinitionsSuccess, FOnGetListDefinitionsError, FOnGetListDefinitionsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetListDefinitionsRequest, UListDefinitionsResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetListDefinitionsRequest*, FOnGetListDefinitionsSuccess, FOnGetListDefinitionsError, FOnGetListDefinitionsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetListDefinitionsRequest*, TBeamFullResponseHandler<UGetListDefinitionsRequest*, UListDefinitionsResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetListDefinitionsRequest*,
                                                                                   TBeamFullResponseHandler<UGetListDefinitionsRequest*, UListDefinitionsResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostAnnouncementsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostAnnouncementsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostAnnouncementsRequest, UEmptyResponse>(
	const int64&, UPostAnnouncementsRequest*, FOnPostAnnouncementsSuccess, FOnPostAnnouncementsError, FOnPostAnnouncementsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostAnnouncementsRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostAnnouncementsRequest*, FOnPostAnnouncementsSuccess, FOnPostAnnouncementsError, FOnPostAnnouncementsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostAnnouncementsRequest*, TBeamFullResponseHandler<UPostAnnouncementsRequest*, UEmptyResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostAnnouncementsRequest*,
                                                                                   TBeamFullResponseHandler<UPostAnnouncementsRequest*, UEmptyResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UBasicAnnouncementsDeleteAnnouncementsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UBasicAnnouncementsDeleteAnnouncementsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UBasicAnnouncementsDeleteAnnouncementsRequest, UEmptyResponse>(
	const int64&, UBasicAnnouncementsDeleteAnnouncementsRequest*, FOnBasicAnnouncementsDeleteAnnouncementsSuccess, FOnBasicAnnouncementsDeleteAnnouncementsError, FOnBasicAnnouncementsDeleteAnnouncementsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UBasicAnnouncementsDeleteAnnouncementsRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicAnnouncementsDeleteAnnouncementsRequest*, FOnBasicAnnouncementsDeleteAnnouncementsSuccess, FOnBasicAnnouncementsDeleteAnnouncementsError, FOnBasicAnnouncementsDeleteAnnouncementsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UBasicAnnouncementsDeleteAnnouncementsRequest*, TBeamFullResponseHandler<UBasicAnnouncementsDeleteAnnouncementsRequest*, UEmptyResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicAnnouncementsDeleteAnnouncementsRequest*,
                                                                                   TBeamFullResponseHandler<UBasicAnnouncementsDeleteAnnouncementsRequest*, UEmptyResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UBasicAnnouncementsGetContentRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UBasicAnnouncementsGetContentRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UBasicAnnouncementsGetContentRequest, UAnnouncementContentResponse>(
	const int64&, UBasicAnnouncementsGetContentRequest*, FOnBasicAnnouncementsGetContentSuccess, FOnBasicAnnouncementsGetContentError, FOnBasicAnnouncementsGetContentComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UBasicAnnouncementsGetContentRequest, UAnnouncementContentResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicAnnouncementsGetContentRequest*, FOnBasicAnnouncementsGetContentSuccess, FOnBasicAnnouncementsGetContentError, FOnBasicAnnouncementsGetContentComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UBasicAnnouncementsGetContentRequest*, TBeamFullResponseHandler<UBasicAnnouncementsGetContentRequest*, UAnnouncementContentResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicAnnouncementsGetContentRequest*,
                                                                                   TBeamFullResponseHandler<UBasicAnnouncementsGetContentRequest*, UAnnouncementContentResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutReadRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutReadRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutReadRequest, UCommonResponse>(
	const int64&, UPutReadRequest*, FOnPutReadSuccess, FOnPutReadError, FOnPutReadComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutReadRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutReadRequest*, FOnPutReadSuccess, FOnPutReadError, FOnPutReadComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutReadRequest*, TBeamFullResponseHandler<UPutReadRequest*, UCommonResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutReadRequest*,
                                                                                   TBeamFullResponseHandler<UPutReadRequest*, UCommonResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UObjectAnnouncementsPostClaimRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UObjectAnnouncementsPostClaimRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UObjectAnnouncementsPostClaimRequest, UCommonResponse>(
	const int64&, UObjectAnnouncementsPostClaimRequest*, FOnObjectAnnouncementsPostClaimSuccess, FOnObjectAnnouncementsPostClaimError, FOnObjectAnnouncementsPostClaimComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UObjectAnnouncementsPostClaimRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UObjectAnnouncementsPostClaimRequest*, FOnObjectAnnouncementsPostClaimSuccess, FOnObjectAnnouncementsPostClaimError, FOnObjectAnnouncementsPostClaimComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UObjectAnnouncementsPostClaimRequest*, TBeamFullResponseHandler<UObjectAnnouncementsPostClaimRequest*, UCommonResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UObjectAnnouncementsPostClaimRequest*,
                                                                                   TBeamFullResponseHandler<UObjectAnnouncementsPostClaimRequest*, UCommonResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetRawRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetRawRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetRawRequest, UAnnouncementRawResponse>(
	const int64&, UGetRawRequest*, FOnGetRawSuccess, FOnGetRawError, FOnGetRawComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetRawRequest, UAnnouncementRawResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetRawRequest*, FOnGetRawSuccess, FOnGetRawError, FOnGetRawComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetRawRequest*, TBeamFullResponseHandler<UGetRawRequest*, UAnnouncementRawResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetRawRequest*,
                                                                                   TBeamFullResponseHandler<UGetRawRequest*, UAnnouncementRawResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetAnnouncementsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetAnnouncementsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetAnnouncementsRequest, UAnnouncementQueryResponse>(
	const int64&, UGetAnnouncementsRequest*, FOnGetAnnouncementsSuccess, FOnGetAnnouncementsError, FOnGetAnnouncementsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetAnnouncementsRequest, UAnnouncementQueryResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetAnnouncementsRequest*, FOnGetAnnouncementsSuccess, FOnGetAnnouncementsError, FOnGetAnnouncementsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetAnnouncementsRequest*, TBeamFullResponseHandler<UGetAnnouncementsRequest*, UAnnouncementQueryResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetAnnouncementsRequest*,
                                                                                   TBeamFullResponseHandler<UGetAnnouncementsRequest*, UAnnouncementQueryResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UObjectAnnouncementsDeleteAnnouncementsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UObjectAnnouncementsDeleteAnnouncementsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UObjectAnnouncementsDeleteAnnouncementsRequest, UCommonResponse>(
	const int64&, UObjectAnnouncementsDeleteAnnouncementsRequest*, FOnObjectAnnouncementsDeleteAnnouncementsSuccess, FOnObjectAnnouncementsDeleteAnnouncementsError, FOnObjectAnnouncementsDeleteAnnouncementsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UObjectAnnouncementsDeleteAnnouncementsRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UObjectAnnouncementsDeleteAnnouncementsRequest*, FOnObjectAnnouncementsDeleteAnnouncementsSuccess, FOnObjectAnnouncementsDeleteAnnouncementsError, FOnObjectAnnouncementsDeleteAnnouncementsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UObjectAnnouncementsDeleteAnnouncementsRequest*, TBeamFullResponseHandler<UObjectAnnouncementsDeleteAnnouncementsRequest*, UCommonResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UObjectAnnouncementsDeleteAnnouncementsRequest*,
                                                                                   TBeamFullResponseHandler<UObjectAnnouncementsDeleteAnnouncementsRequest*, UCommonResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetTemplateRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetTemplateRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetTemplateRequest, UMailTemplate>(
	const int64&, UGetTemplateRequest*, FOnGetTemplateSuccess, FOnGetTemplateError, FOnGetTemplateComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetTemplateRequest, UMailTemplate>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetTemplateRequest*, FOnGetTemplateSuccess, FOnGetTemplateError, FOnGetTemplateComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetTemplateRequest*, TBeamFullResponseHandler<UGetTemplateRequest*, UMailTemplate*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetTemplateRequest*,
                                                                                   TBeamFullResponseHandler<UGetTemplateRequest*, UMailTemplate*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UBasicMailGetMailRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UBasicMailGetMailRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UBasicMailGetMailRequest, UMailResponse>(
	const int64&, UBasicMailGetMailRequest*, FOnBasicMailGetMailSuccess, FOnBasicMailGetMailError, FOnBasicMailGetMailComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UBasicMailGetMailRequest, UMailResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicMailGetMailRequest*, FOnBasicMailGetMailSuccess, FOnBasicMailGetMailError, FOnBasicMailGetMailComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UBasicMailGetMailRequest*, TBeamFullResponseHandler<UBasicMailGetMailRequest*, UMailResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicMailGetMailRequest*,
                                                                                   TBeamFullResponseHandler<UBasicMailGetMailRequest*, UMailResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetDetailRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetDetailRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetDetailRequest, UMailResponse>(
	const int64&, UGetDetailRequest*, FOnGetDetailSuccess, FOnGetDetailError, FOnGetDetailComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetDetailRequest, UMailResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetDetailRequest*, FOnGetDetailSuccess, FOnGetDetailError, FOnGetDetailComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetDetailRequest*, TBeamFullResponseHandler<UGetDetailRequest*, UMailResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetDetailRequest*,
                                                                                   TBeamFullResponseHandler<UGetDetailRequest*, UMailResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetCategoriesRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetCategoriesRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetCategoriesRequest, UListMailCategoriesResponse>(
	const int64&, UGetCategoriesRequest*, FOnGetCategoriesSuccess, FOnGetCategoriesError, FOnGetCategoriesComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetCategoriesRequest, UListMailCategoriesResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetCategoriesRequest*, FOnGetCategoriesSuccess, FOnGetCategoriesError, FOnGetCategoriesComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetCategoriesRequest*, TBeamFullResponseHandler<UGetCategoriesRequest*, UListMailCategoriesResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetCategoriesRequest*,
                                                                                   TBeamFullResponseHandler<UGetCategoriesRequest*, UListMailCategoriesResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UObjectMailPostSearchRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UObjectMailPostSearchRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UObjectMailPostSearchRequest, UMailSearchResponse>(
	const int64&, UObjectMailPostSearchRequest*, FOnObjectMailPostSearchSuccess, FOnObjectMailPostSearchError, FOnObjectMailPostSearchComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UObjectMailPostSearchRequest, UMailSearchResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UObjectMailPostSearchRequest*, FOnObjectMailPostSearchSuccess, FOnObjectMailPostSearchError, FOnObjectMailPostSearchComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UObjectMailPostSearchRequest*, TBeamFullResponseHandler<UObjectMailPostSearchRequest*, UMailSearchResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UObjectMailPostSearchRequest*,
                                                                                   TBeamFullResponseHandler<UObjectMailPostSearchRequest*, UMailSearchResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutBulkRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutBulkRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutBulkRequest, UMailSuccessResponse>(
	const int64&, UPutBulkRequest*, FOnPutBulkSuccess, FOnPutBulkError, FOnPutBulkComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutBulkRequest, UMailSuccessResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutBulkRequest*, FOnPutBulkSuccess, FOnPutBulkError, FOnPutBulkComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutBulkRequest*, TBeamFullResponseHandler<UPutBulkRequest*, UMailSuccessResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutBulkRequest*,
                                                                                   TBeamFullResponseHandler<UPutBulkRequest*, UMailSuccessResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutAcceptManyRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutAcceptManyRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutAcceptManyRequest, UMailSuccessResponse>(
	const int64&, UPutAcceptManyRequest*, FOnPutAcceptManySuccess, FOnPutAcceptManyError, FOnPutAcceptManyComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutAcceptManyRequest, UMailSuccessResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutAcceptManyRequest*, FOnPutAcceptManySuccess, FOnPutAcceptManyError, FOnPutAcceptManyComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutAcceptManyRequest*, TBeamFullResponseHandler<UPutAcceptManyRequest*, UMailSuccessResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutAcceptManyRequest*,
                                                                                   TBeamFullResponseHandler<UPutAcceptManyRequest*, UMailSuccessResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UObjectMailGetMailRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UObjectMailGetMailRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UObjectMailGetMailRequest, UMailQueryResponse>(
	const int64&, UObjectMailGetMailRequest*, FOnObjectMailGetMailSuccess, FOnObjectMailGetMailError, FOnObjectMailGetMailComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UObjectMailGetMailRequest, UMailQueryResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UObjectMailGetMailRequest*, FOnObjectMailGetMailSuccess, FOnObjectMailGetMailError, FOnObjectMailGetMailComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UObjectMailGetMailRequest*, TBeamFullResponseHandler<UObjectMailGetMailRequest*, UMailQueryResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UObjectMailGetMailRequest*,
                                                                                   TBeamFullResponseHandler<UObjectMailGetMailRequest*, UMailQueryResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UObjectMailPutMailRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UObjectMailPutMailRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UObjectMailPutMailRequest, UMailSuccessResponse>(
	const int64&, UObjectMailPutMailRequest*, FOnObjectMailPutMailSuccess, FOnObjectMailPutMailError, FOnObjectMailPutMailComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UObjectMailPutMailRequest, UMailSuccessResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UObjectMailPutMailRequest*, FOnObjectMailPutMailSuccess, FOnObjectMailPutMailError, FOnObjectMailPutMailComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UObjectMailPutMailRequest*, TBeamFullResponseHandler<UObjectMailPutMailRequest*, UMailSuccessResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UObjectMailPutMailRequest*,
                                                                                   TBeamFullResponseHandler<UObjectMailPutMailRequest*, UMailSuccessResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutAttachmentsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutAttachmentsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutAttachmentsRequest, UMailSuccessResponse>(
	const int64&, UPutAttachmentsRequest*, FOnPutAttachmentsSuccess, FOnPutAttachmentsError, FOnPutAttachmentsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutAttachmentsRequest, UMailSuccessResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutAttachmentsRequest*, FOnPutAttachmentsSuccess, FOnPutAttachmentsError, FOnPutAttachmentsComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutAttachmentsRequest*, TBeamFullResponseHandler<UPutAttachmentsRequest*, UMailSuccessResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutAttachmentsRequest*,
                                                                                   TBeamFullResponseHandler<UPutAttachmentsRequest*, UMailSuccessResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UBasicMailPutMailRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UBasicMailPutMailRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UBasicMailPutMailRequest, UMailSuccessResponse>(
	const int64&, UBasicMailPutMailRequest*, FOnBasicMailPutMailSuccess, FOnBasicMailPutMailError, FOnBasicMailPutMailComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UBasicMailPutMailRequest, UMailSuccessResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicMailPutMailRequest*, FOnBasicMailPutMailSuccess, FOnBasicMailPutMailError, FOnBasicMailPutMailComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UBasicMailPutMailRequest*, TBeamFullResponseHandler<UBasicMailPutMailRequest*, UMailSuccessResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicMailPutMailRequest*,
                                                                                   TBeamFullResponseHandler<UBasicMailPutMailRequest*, UMailSuccessResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UBasicMailPostBulkRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UBasicMailPostBulkRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UBasicMailPostBulkRequest, UMailSuccessResponse>(
	const int64&, UBasicMailPostBulkRequest*, FOnBasicMailPostBulkSuccess, FOnBasicMailPostBulkError, FOnBasicMailPostBulkComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UBasicMailPostBulkRequest, UMailSuccessResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicMailPostBulkRequest*, FOnBasicMailPostBulkSuccess, FOnBasicMailPostBulkError, FOnBasicMailPostBulkComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UBasicMailPostBulkRequest*, TBeamFullResponseHandler<UBasicMailPostBulkRequest*, UMailSuccessResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicMailPostBulkRequest*,
                                                                                   TBeamFullResponseHandler<UBasicMailPostBulkRequest*, UMailSuccessResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UObjectMailPostBulkRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UObjectMailPostBulkRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UObjectMailPostBulkRequest, UMailSuccessResponse>(
	const int64&, UObjectMailPostBulkRequest*, FOnObjectMailPostBulkSuccess, FOnObjectMailPostBulkError, FOnObjectMailPostBulkComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UObjectMailPostBulkRequest, UMailSuccessResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UObjectMailPostBulkRequest*, FOnObjectMailPostBulkSuccess, FOnObjectMailPostBulkError, FOnObjectMailPostBulkComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UObjectMailPostBulkRequest*, TBeamFullResponseHandler<UObjectMailPostBulkRequest*, UMailSuccessResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UObjectMailPostBulkRequest*,
                                                                                   TBeamFullResponseHandler<UObjectMailPostBulkRequest*, UMailSuccessResponse*>, const UObject*);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostMailRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostMailRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostMailRequest, USendMailResponse>(
	const int64&, UPostMailRequest*, FOnPostMailSuccess, FOnPostMailError, FOnPostMailComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostMailRequest, USendMailResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostMailRequest*, FOnPostMailSuccess, FOnPostMailError, FOnPostMailComplete, const UObject*);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostMailRequest*, TBeamFullResponseHandler<UPostMailRequest*, USendMailResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostMailRequest*,
                                                                                   TBeamFullResponseHandler<UPostMailRequest*, USendMailResponse*>, const UObject*);

